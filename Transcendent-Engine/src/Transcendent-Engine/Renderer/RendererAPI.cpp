#include "tepch.h"
#include "Transcendent-Engine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace TE {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::Vulkan;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::NONE:       TE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");      return nullptr;
			case RendererAPI::API::DirectX12:  TE_CORE_ASSERT(false, "RendererAPI::DirectX12 is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:     return CreateScope<OpenGLRendererAPI>();
			case RendererAPI::API::Vulkan:     return CreateScope<VulkanRendererAPI>();
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
