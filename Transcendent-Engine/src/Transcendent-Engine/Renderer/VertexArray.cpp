#include "tepch.h"
#include "Transcendent-Engine/Renderer/VertexArray.h"

#include "Transcendent-Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace TE {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}