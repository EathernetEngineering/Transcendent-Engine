#pragma once

#include "Transcendent-Engine/Renderer/RendererAPI.h"
#include <Platform/Vulkan/VulkanVertexArray.h>

#define VULKAN_HPP_NO_EXCEPTIONS
#define VULKAN_HPP_TYPESAFE_CONVERSION
#include <vulkan/vulkan.hpp>
#include <vulkan/vk_sdk_platform.h>

namespace TE {

	class VulkanRendererAPI : public RendererAPI
	{
	public:
		VulkanRendererAPI();
		virtual ~VulkanRendererAPI();

		void Init() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void DrawIndexed(const Ref<VertexArray>& VertexArray, size_t Count) override;

		void BeginScene() override;
		void EndScene() override;

		inline vk::Device* GetDevice() { TE_CORE_ASSERT(m_Initalized, "Must initalize renderer first");  return &m_Device; }
		inline vk::PhysicalDevice* GetGpu() { TE_CORE_ASSERT(m_Initalized, "Must initalize renderer first");  return &m_Gpu; }
		inline vk::SwapchainKHR* GetSwapchain() { TE_CORE_ASSERT(m_Initalized, "Must initalize renderer first"); return &m_Swapchain; }
		inline vk::SurfaceKHR* GetSurface() { TE_CORE_ASSERT(m_Initalized, "Must initalize renderer first"); return &m_Surface; }

		inline vk::Format GetFormat() const { return m_Format; }
		inline vk::ColorSpaceKHR GetColorSpace() const { return m_ColorSpace; }

		static VulkanRendererAPI* Get() { return s_Instance; }

	private:
		void InitSwapchain();
		void CreateDevice();

	private:
		uint32_t m_EnabledExtensionCount;
		const char* m_ExtensionNames[64];

		vk::Instance m_Inst;
		
		uint32_t m_GpuNumber;
		vk::PhysicalDevice m_Gpu;
		vk::PhysicalDeviceProperties m_GpuProps;
		vk::PhysicalDeviceMemoryProperties m_MemoryProperties;

		vk::Device m_Device;

		vk::Queue m_GraphicsQueue;
		vk::Queue m_PresentQueue;

		uint32_t m_QueueFamilyCount;

		vk::SurfaceKHR m_Surface;

		vk::Format m_Format;
		vk::ColorSpaceKHR m_ColorSpace;

		static constexpr uint32_t m_FrameBufferSize = 2;
		uint32_t m_FrameIndex;
		vk::Fence m_Fences[2];
		vk::Semaphore m_ImageAcquiredSemaphores[m_FrameBufferSize];
		vk::Semaphore m_DrawCompleteSemaphores[m_FrameBufferSize];
		vk::Semaphore m_ImageOwnershipSemaphores[m_FrameBufferSize];

		Scope<vk::QueueFamilyProperties[]> m_QueueProps;

		uint32_t m_GraphicsQueueFamilyIndex;
		uint32_t m_PresentQueueFamilyIndex;
		bool m_SeperatePresentQueue;

	private:
		vk::CommandPool m_CmdPool;
		vk::CommandBuffer m_Cmd;

		vk::SwapchainKHR m_Swapchain;

	private:
		glm::vec4 m_ClearColor;
	
	private:
		bool m_Initalized = false;

	private:
		static VulkanRendererAPI* s_Instance;
	};
}
