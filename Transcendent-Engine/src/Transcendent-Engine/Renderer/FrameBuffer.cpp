#include "tepch.h"
#include "FrameBuffer.h"

#include <Transcendent-Engine/Renderer/Renderer.h>

#include <Platform/OpenGL/OpenGLFrameBuffer.h>
#include <Platform/Vulkan/VulkanFrameBuffer.h>

namespace TE {

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec) 
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE:       TE_CORE_ASSERT(false, "RendererAPI:NONE is currently not supported!"); return nullptr;
			case RendererAPI::API::DirectX12:  TE_CORE_ASSERT(false, "RendererAPI::DirectX12 is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:     return CreateRef<OpenGLFrameBuffer>(spec);
			case RendererAPI::API::Vulkan:     return CreateRef<VulkanFrameBuffer>(spec);
		}
		
		TE_CORE_ASSERT(false, "UnKnown Renderer API");
		return nullptr;
	}

}
