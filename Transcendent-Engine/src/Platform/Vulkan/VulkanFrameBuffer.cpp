#include <tepch.h>

#include <Platform/Vulkan/VulkanFrameBuffer.h>
#include <Platform/Vulkan/VulkanRendererAPI.h>

namespace TE {

	VulkanFrameBuffer::VulkanFrameBuffer(const FrameBufferSpecification& Spec)
		: m_Spec(Spec)
	{
		this->Invalidate();
	}

	void VulkanFrameBuffer::Invalidate()
	{
		vk::PhysicalDevice* gpu = VulkanRendererAPI::Get()->GetGpu();
		vk::Device* device = VulkanRendererAPI::Get()->GetDevice();

		vk::SwapchainKHR PrevSwapchain = *VulkanRendererAPI::Get()->GetSwapchain();

		vk::SurfaceCapabilitiesKHR surfaceCapabilities;
		auto result = gpu->getSurfaceCapabilitiesKHR(*(VulkanRendererAPI::Get()->GetSurface()), &surfaceCapabilities);
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get surface capabilities");

		uint32_t presentModeCount;
		result = gpu->getSurfacePresentModesKHR(*(VulkanRendererAPI::Get()->GetSurface()), &presentModeCount, static_cast<vk::PresentModeKHR*>(nullptr));
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get surface present mode count");

		Scope<vk::PresentModeKHR[]> PresentModes(new vk::PresentModeKHR[presentModeCount]);
		result = gpu->getSurfacePresentModesKHR(*(VulkanRendererAPI::Get()->GetSurface()), &presentModeCount, PresentModes.get());
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get surface modes");

		vk::Extent2D swapchainExtent;

		if (surfaceCapabilities.currentExtent.width == (uint32_t)-1 || surfaceCapabilities.currentExtent.height == (uint32_t)-1)
		{
			swapchainExtent.width = m_Spec.Height;
			swapchainExtent.height = m_Spec.Height;
		}
		else
		{
			swapchainExtent = surfaceCapabilities.currentExtent;
			// TODO: Think about having swapchain update frame buffer spec
		}

		vk::PresentModeKHR swapchainPresentMode = vk::PresentModeKHR::eFifo;

		uint32_t desiredNumberOfSwapChainImages = 3;
		if (desiredNumberOfSwapChainImages < surfaceCapabilities.minImageCount)
		{
			desiredNumberOfSwapChainImages = surfaceCapabilities.minImageCount;
		}

		if (surfaceCapabilities.maxImageCount > 0 && desiredNumberOfSwapChainImages > surfaceCapabilities.maxImageCount)
		{
			desiredNumberOfSwapChainImages = surfaceCapabilities.maxImageCount;
		}

		vk::SurfaceTransformFlagBitsKHR preTransform;
		if (surfaceCapabilities.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity)
		{
			preTransform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
		}
		else
		{
			preTransform = surfaceCapabilities.currentTransform;
		}

		vk::CompositeAlphaFlagBitsKHR compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		vk::CompositeAlphaFlagBitsKHR compositeAlphaFlags[] = {
			vk::CompositeAlphaFlagBitsKHR::eOpaque,
			vk::CompositeAlphaFlagBitsKHR::ePreMultiplied,
			vk::CompositeAlphaFlagBitsKHR::ePostMultiplied,
			vk::CompositeAlphaFlagBitsKHR::eInherit
		};

		for (uint32_t i = 0; i < _countof(compositeAlphaFlags); i++)
		{
			if (surfaceCapabilities.supportedCompositeAlpha & compositeAlphaFlags[i])
			{
				compositeAlpha = compositeAlphaFlags[i];
				break;
			}
		}

		auto const swapchainCi = vk::SwapchainCreateInfoKHR()
			.setSurface(*(VulkanRendererAPI::Get()->GetSurface()))
			.setMinImageCount(desiredNumberOfSwapChainImages)
			.setImageFormat(VulkanRendererAPI::Get()->GetFormat())
			.setImageColorSpace(VulkanRendererAPI::Get()->GetColorSpace())
			.setImageExtent({ swapchainExtent.width, swapchainExtent.height })
			.setImageArrayLayers(1)
			.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
			.setImageSharingMode(vk::SharingMode::eExclusive)
			.setQueueFamilyIndexCount(0)
			.setPQueueFamilyIndices(nullptr)
			.setPreTransform(preTransform)
			.setCompositeAlpha(compositeAlpha)
			.setPresentMode(swapchainPresentMode)
			.setClipped(true)
			.setOldSwapchain(PrevSwapchain);

		result = VulkanRendererAPI::Get()->GetDevice()->createSwapchainKHR(&swapchainCi, nullptr, VulkanRendererAPI::Get()->GetSwapchain());
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to create swapchain");

		if (PrevSwapchain)
		{
			VulkanRendererAPI::Get()->GetDevice()->destroySwapchainKHR(PrevSwapchain, nullptr);
		}

		result = device->getSwapchainImagesKHR(*(VulkanRendererAPI::Get()->GetSwapchain()), &m_SwapchainImageCount, static_cast<vk::Image*>(nullptr));
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get swaphain image count");

		Scope<vk::Image[]> swapchainImages(new vk::Image[m_SwapchainImageCount]);
		result = device->getSwapchainImagesKHR(*(VulkanRendererAPI::Get()->GetSwapchain()), &m_SwapchainImageCount, swapchainImages.get());
		TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to get swaphain images");

		m_SwapchainImageResources.reset(new VkSwapchainImageResources[m_SwapchainImageCount]);

		for (uint32_t i = 0; i < m_SwapchainImageCount; i++)
		{
			auto colorImageView = vk::ImageViewCreateInfo()
				.setViewType(vk::ImageViewType::e2D)
				.setFormat(VulkanRendererAPI::Get()->GetFormat())
				.setSubresourceRange(vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));

			m_SwapchainImageResources[i].image = swapchainImages[i];

			colorImageView.image = m_SwapchainImageResources[i].image;

			result = device->createImageView(&colorImageView, nullptr, &m_SwapchainImageResources[i].view);
			TE_CORE_ASSERT(result == vk::Result::eSuccess, "Failed to create image view");
		}
	}

	void VulkanFrameBuffer::Bind()
	{

	}

	void VulkanFrameBuffer::Unbind()
	{

	}

	void VulkanFrameBuffer::UpdateSpecification(FrameBufferSpecification Spec)
	{
		m_Spec = Spec;
		Invalidate();
	}

}
