#include <tepch.h>
#include <Platform/Vulkan/VulkanRendererAPI.h>

#include <Transcendent-Engine/core/Application.h>

namespace TE {

	VulkanRendererAPI* VulkanRendererAPI::s_Instance;

	VulkanRendererAPI::VulkanRendererAPI()
		: m_EnabledExtensionCount(0), m_GpuNumber(0), m_Device(nullptr), m_Swapchain(nullptr)
	{
		s_Instance = this;
	}

	VulkanRendererAPI::~VulkanRendererAPI()
	{
		memset(this, 0, sizeof(VulkanRendererAPI));
		delete this;
	}

	void VulkanRendererAPI::Init()
	{
		TE_CORE_INFO("Initializing Vulkan");
		m_Initalized = true;
		vk::Result result;

		char const* const instanceValidationLayers[] = { "VK_LAYER_KHRONOS_validation" };
		uint32_t instanceExtensionCount = 0;

		vk::Bool32 surfaceExtFound = VK_FALSE;
		vk::Bool32 platformSurfaceExtFound = VK_FALSE;

		memset(m_ExtensionNames, 0, sizeof(m_ExtensionNames));

		result = vk::enumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount,
			static_cast<vk::ExtensionProperties*>(nullptr));
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to enumerate extension properties");

		if (instanceExtensionCount > 0) {
			Scope<vk::ExtensionProperties[]> instance_extensions(new vk::ExtensionProperties[instanceExtensionCount]);
			result = vk::enumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, instance_extensions.get());
			TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to enumerate extension properties");

			for (uint32_t i = 0; i < instanceExtensionCount; i++) {
				if (!strcmp(VK_KHR_SURFACE_EXTENSION_NAME, instance_extensions[i].extensionName)) {
					surfaceExtFound = 1;
					m_ExtensionNames[m_EnabledExtensionCount++] = VK_KHR_SURFACE_EXTENSION_NAME;
				}
				if (!strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, instance_extensions[i].extensionName)) {
					platformSurfaceExtFound = 1;
					m_ExtensionNames[m_EnabledExtensionCount++] = VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
				}
				TE_CORE_ASSERT(m_EnabledExtensionCount < 64, "Enabled extension count exceeded 64, Please use less extensions");
			}
		}

		vk::ApplicationInfo const app = vk::ApplicationInfo()
			.setPApplicationName("Transcendent-Engine")
			.setApplicationVersion(0)
			.setPEngineName("Transcendent-Engine")
			.setEngineVersion(0)
			.setApiVersion(VK_API_VERSION_1_0);

		vk::InstanceCreateInfo const instInfo = vk::InstanceCreateInfo()
			.setPApplicationInfo(&app)
			.setEnabledLayerCount(0)
			.setPpEnabledLayerNames(instanceValidationLayers)
			.setEnabledExtensionCount(m_EnabledExtensionCount)
			.setPpEnabledExtensionNames(m_ExtensionNames);

		result = vk::createInstance(&instInfo, nullptr, &m_Inst);
		switch (result) {
			case vk::Result::eSuccess: break;
			case vk::Result::eErrorIncompatibleDriver: TE_CORE_ASSERT(false, "Incompatible Driver"); return;
			case vk::Result::eErrorExtensionNotPresent: TE_CORE_ASSERT(false, "Extension not present"); return;
			default: TE_CORE_ASSERT(false, "Unknown error creating instance"); return;
		}
		uint32_t GpuCount;
		result = m_Inst.enumeratePhysicalDevices(&GpuCount, static_cast<vk::PhysicalDevice*>(nullptr));
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to enumerate physical devices");

		if (GpuCount > 0)
		{
			Scope<vk::PhysicalDevice[]> PhysicalDevices(new vk::PhysicalDevice[GpuCount]);
			result = m_Inst.enumeratePhysicalDevices(&GpuCount, PhysicalDevices.get());
			TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get physical devices");

			if (m_GpuNumber > GpuCount - 1)
			{
				TE_CORE_ERROR("GPU {0} was specified, but is not present. GPU count is {1}", m_GpuNumber, GpuCount);
				TE_CORE_ERROR("Continuing with GPU 0 (default)");
				m_GpuNumber = 0;
			}
			else
			{
				if (m_GpuNumber == 0)
					TE_CORE_INFO("Using GPU {0} (default)", m_GpuNumber);
				else
					TE_CORE_INFO("Using GPU {0}", m_GpuNumber);
			}
			m_Gpu = PhysicalDevices[m_GpuNumber];
		}
		else
		{
			TE_CORE_ASSERT(false, "No physical deviecs present");
		}

		uint32_t DeviceExtensionCount = 0;
		vk::Bool32 SwapchainExtFound = VK_FALSE;
		m_EnabledExtensionCount = 0;
		memset(m_ExtensionNames, 0, sizeof(m_ExtensionNames));

		result = m_Gpu.enumerateDeviceExtensionProperties(nullptr, &DeviceExtensionCount, static_cast<vk::ExtensionProperties*>(nullptr));
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to enumerate device extensions");

		if (DeviceExtensionCount > 0) {
			Scope<vk::ExtensionProperties[]> DeviceExtensions(new vk::ExtensionProperties[DeviceExtensionCount]);
			result = m_Gpu.enumerateDeviceExtensionProperties(nullptr, &DeviceExtensionCount, DeviceExtensions.get());
			TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get device extensions");

			for (uint32_t i = 0; i < DeviceExtensionCount; i++) {
				if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, DeviceExtensions[i].extensionName)) {
					SwapchainExtFound = 1;
					m_ExtensionNames[m_EnabledExtensionCount++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
				}
				TE_CORE_ASSERT(m_EnabledExtensionCount < 64, "Enabled extension count exceeded 64, Please use less extensions");
			}
		}

		if (!SwapchainExtFound)
		{
			char err[512];
			sprintf_s(err, "vkEnumerateDeviceExtensionProperties failed to find the %s extension.\n\nDo you have a compatible Vulkan installable client driver (ICD) installed?\nPlease look at the Getting Started guide for additional information.\nvkCreateInstance Failure", VK_KHR_SWAPCHAIN_EXTENSION_NAME);
			TE_CORE_ASSERT(false, err);
		}

		m_Gpu.getProperties(&m_GpuProps);

		TE_CORE_INFO("Vulkan Info:");
		TE_CORE_INFO("    Vendor:    {0}", m_GpuProps.vendorID);
		TE_CORE_INFO("  Renderer:    {0}", m_GpuProps.deviceName);
		TE_CORE_INFO("   Version:    {0} {1}", m_GpuProps.apiVersion, m_GpuProps.driverVersion);
		TE_CORE_INFO("     VSync:    {0}", Application::Get().GetWindow().IsVSync());

		m_Gpu.getQueueFamilyProperties(&m_QueueFamilyCount, static_cast<vk::QueueFamilyProperties*>(nullptr));

		TE_CORE_ASSERT(m_QueueFamilyCount >= 1, "Queue family count < 1");

		m_QueueProps.reset(new vk::QueueFamilyProperties[m_QueueFamilyCount]);
		m_Gpu.getQueueFamilyProperties(&m_QueueFamilyCount, m_QueueProps.get());

		vk::PhysicalDeviceFeatures PhysicalDeviceFeatures;
		m_Gpu.getFeatures(&PhysicalDeviceFeatures);

		InitSwapchain();
	}

	void VulkanRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{

	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
		m_ClearColor = color;
	}

	void VulkanRendererAPI::Clear()
	{

	}

	void VulkanRendererAPI::DrawIndexed(const Ref<VertexArray>& VertexArray, size_t Count)
	{

	}

	void VulkanRendererAPI::BeginScene()
	{

	}

	void VulkanRendererAPI::EndScene()
	{

	}

	void VulkanRendererAPI::InitSwapchain()
	{
		vk::Win32SurfaceCreateInfoKHR createInfo = vk::Win32SurfaceCreateInfoKHR()
			.setHinstance(GetModuleHandle(NULL))
			.setHwnd(static_cast<HWND>(Application::Get().GetWindow().GetNativeWindow()));

		vk::Result result = m_Inst.createWin32SurfaceKHR(&createInfo, nullptr, &m_Surface);
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to create surface");

		Scope<vk::Bool32[]> supportsPresent(new vk::Bool32[m_QueueFamilyCount]);
		for (uint32_t i = 0; i < m_QueueFamilyCount; i++)
		{
			result = m_Gpu.getSurfaceSupportKHR(i, m_Surface, &supportsPresent[i]);
			TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get suface support");
		}

		uint32_t graphicsQueueFamilyIndex = UINT32_MAX;
		uint32_t presentQueueFamilyIndex = UINT32_MAX;
		for (uint32_t i = 0; i < m_QueueFamilyCount; i++)
		{
			if (m_QueueProps[i].queueFlags & vk::QueueFlagBits::eGraphics)
			{
				if (graphicsQueueFamilyIndex == UINT32_MAX)
				{
					graphicsQueueFamilyIndex = i;
				}
				if (supportsPresent[i] == VK_TRUE)
				{
					graphicsQueueFamilyIndex = i;
					presentQueueFamilyIndex = i;
					break;
				}
			}
		}

		if (presentQueueFamilyIndex == UINT32_MAX)
		{
			for (uint32_t i = 0; i < m_QueueFamilyCount; i++)
			{
				if (supportsPresent[i] == VK_TRUE)
				{
					presentQueueFamilyIndex = i;
					break;
				}
			}
		}

		if (graphicsQueueFamilyIndex == UINT32_MAX || presentQueueFamilyIndex == UINT32_MAX)
		{
			TE_CORE_ASSERT(false, "Could not find both graphics and present queues\n", "Swapchain Initialization Failure")
		}

		m_GraphicsQueueFamilyIndex = graphicsQueueFamilyIndex;
		m_PresentQueueFamilyIndex = presentQueueFamilyIndex;
		m_SeperatePresentQueue = graphicsQueueFamilyIndex != presentQueueFamilyIndex;

		CreateDevice();

		m_Device.getQueue(m_GraphicsQueueFamilyIndex, 0, &m_GraphicsQueue);
		m_SeperatePresentQueue ? m_Device.getQueue(m_PresentQueueFamilyIndex, 0, &m_PresentQueue) : m_PresentQueue = m_GraphicsQueue;

		uint32_t formatCount;
		result = m_Gpu.getSurfaceFormatsKHR(m_Surface, &formatCount, static_cast<vk::SurfaceFormatKHR*>(nullptr));
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get foramt count");

		Scope<vk::SurfaceFormatKHR[]> surfaceFormats(new vk::SurfaceFormatKHR[formatCount]);
		result = m_Gpu.getSurfaceFormatsKHR(m_Surface, &formatCount, surfaceFormats.get());
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get surface formats");

		if (formatCount == 1 && surfaceFormats[0] == vk::Format::eUndefined)
		{
			m_Format = vk::Format::eB8G8R8A8Unorm;
		}
		else
		{
			TE_CORE_ASSERT(formatCount >= 1, "Foramt count < 1");
			m_Format = surfaceFormats[0].format;
		}
		m_ColorSpace = surfaceFormats[0].colorSpace;

		vk::SemaphoreCreateInfo semaphoreCreateInfo = vk::SemaphoreCreateInfo();

		vk::FenceCreateInfo FenceCI = vk::FenceCreateInfo().setFlags(vk::FenceCreateFlagBits::eSignaled);
		for (uint32_t i = 0; i < m_FrameBufferSize; i++)
		{
			result = m_Device.createFence(&FenceCI, nullptr, &m_Fences[i]);
			if (result != vk::Result::eSuccess)
			{
				char buff[64];
				sprintf_s(buff, "Failed to craete fence %u", i);
				TE_CORE_ASSERT(false, buff);
			}

			result = m_Device.createSemaphore(&semaphoreCreateInfo, nullptr, &m_ImageAcquiredSemaphores[i]);
			if (result != vk::Result::eSuccess)
			{
				char buff[64];
				sprintf_s(buff, "Failed to craete image image acquired %u", i);
				TE_CORE_ASSERT(false, buff);
			}

			result = m_Device.createSemaphore(&semaphoreCreateInfo, nullptr, &m_DrawCompleteSemaphores[i]);
			if (result != vk::Result::eSuccess)
			{
				char buff[64];
				sprintf_s(buff, "Failed to craete draw complete semaphore %u", i);
				TE_CORE_ASSERT(false, buff);
			}

			if (m_SeperatePresentQueue)
			{
				result = m_Device.createSemaphore(&semaphoreCreateInfo, nullptr, &m_ImageOwnershipSemaphores[i]);
				if (result != vk::Result::eSuccess)
				{
					char buff[64];
					sprintf_s(buff, "Failed to craete image ownership semaphore %u", i);
					TE_CORE_ASSERT(false, buff);
				}
			}
		}
		m_FrameIndex = 0;

		m_Gpu.getMemoryProperties(&m_MemoryProperties);

		auto const CmdPoolInfo = vk::CommandPoolCreateInfo().setQueueFamilyIndex(m_GraphicsQueueFamilyIndex);
		result = m_Device.createCommandPool(&CmdPoolInfo, nullptr, &m_CmdPool);
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to create command pool");

		auto cmd = vk::CommandBufferAllocateInfo()
						.setCommandPool(m_CmdPool)
						.setLevel(vk::CommandBufferLevel::ePrimary)
						.setCommandBufferCount(1);

		result = m_Device.allocateCommandBuffers(&cmd, &m_Cmd);
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to allocate command buffer");

		auto const cmdBufferBeginInfo = vk::CommandBufferBeginInfo().setPInheritanceInfo(nullptr);

		result = m_Cmd.begin(&cmdBufferBeginInfo);
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to begin command list");
	}

	void VulkanRendererAPI::CreateDevice()
	{
		float const priorities[1] = { 0.0 };

		vk::DeviceQueueCreateInfo queues[2];
		queues[0].setQueueFamilyIndex(m_GraphicsQueueFamilyIndex);
		queues[0].setQueueCount(1);
		queues[0].setPQueuePriorities(priorities);

		vk::DeviceCreateInfo deviceInfo = vk::DeviceCreateInfo()
			.setQueueCreateInfoCount(1)
			.setPQueueCreateInfos(queues)
			.setEnabledLayerCount(0)
			.setPpEnabledLayerNames(nullptr)
			.setEnabledExtensionCount(m_EnabledExtensionCount)
			.setPpEnabledExtensionNames((const char* const*)m_ExtensionNames)
			.setPEnabledFeatures(nullptr);

		if (m_SeperatePresentQueue)
		{
			queues[0].setQueueFamilyIndex(m_PresentQueueFamilyIndex);
			queues[0].setQueueCount(1);
			queues[0].setPQueuePriorities(priorities);
			deviceInfo.setQueueCreateInfoCount(2);
		}

		m_Device = vk::Device();

		vk::Result result = m_Gpu.createDevice(&deviceInfo, nullptr, &m_Device);
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to create device");
	}

}
