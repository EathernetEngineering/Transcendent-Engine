#include "tepch.h"
#include "Transcendent-Engine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Windows/DirectX12RendererAPI.h"

namespace TE {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::DirectX12;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::NONE:    TE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		case RendererAPI::API::DirectX12: return CreateScope<DirectX12RendererAPI>();
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
