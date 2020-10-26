#pragma once

#include <Transcendent-Engine/Renderer/FrameBuffer.h>

#include <vulkan/vulkan.hpp>

namespace TE {

	typedef struct {
		vk::Image image;
		vk::CommandBuffer cmd;
		vk::CommandBuffer grpahicsToPresentCmd;
		vk::ImageView view;
		vk::Buffer uniformBuffer;
		vk::DeviceMemory uniformMemory;
		void* uinformMemoryPtr;
		vk::Framebuffer frameBuffer;
		vk::DescriptorSet desciptorSet;
	} VkSwapchainImageResources;

	class VulkanFrameBuffer : public FrameBuffer
	{
	public:
		VulkanFrameBuffer(const FrameBufferSpecification& Spec);

		inline const FrameBufferSpecification& GetSpecification() const { return m_Spec; }

		void Invalidate();
		void Bind();
		void Unbind();

		void UpdateSpecification(FrameBufferSpecification spec);

		inline uint32_t GetColourAttachmentRendererID() const { return 0u; }

	private:
		FrameBufferSpecification m_Spec;

	private:
		uint32_t m_SwapchainImageCount;
		Scope<VkSwapchainImageResources[]> m_SwapchainImageResources;
	};

}
