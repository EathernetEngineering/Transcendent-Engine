#include "tepch.h"
#include "Transcendent-Engine/Renderer/VertexArray.h"
#include "Transcendent-Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/Vulkan/VulkanVertexArray.h"

namespace TE {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:       TE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");      return nullptr;
		case RendererAPI::API::DirectX12:  TE_CORE_ASSERT(false, "RendererAPI::DirectX12 is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:     return CreateRef<OpenGLVertexArray>();
		case RendererAPI::API::Vulkan:     return CreateRef<VulkanVertexArray>();
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref <VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:       TE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");      return nullptr;
		case RendererAPI::API::DirectX12:  TE_CORE_ASSERT(false, "RendererAPI::DirectX12 is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:     return CreateRef<OpenGLVertexBuffer>(vertices, size);
		case RendererAPI::API::Vulkan:     return CreateRef<VulkanVertexBuffer>(vertices, size);
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:       TE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");      return nullptr;
		case RendererAPI::API::DirectX12:  TE_CORE_ASSERT(false, "RendererAPI::DirectX12 is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:     return CreateRef<OpenGLVertexBuffer>(size);
		case RendererAPI::API::Vulkan:     return CreateRef<VulkanVertexBuffer>(size);
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref< IndexBuffer> IndexBuffer::Create(uint32_t* indices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:       TE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");      return nullptr;
		case RendererAPI::API::DirectX12:  TE_CORE_ASSERT(false, "RendererAPI::DirectX12 is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:     return CreateRef<OpenGLIndexBuffer>(indices, size);
		case RendererAPI::API::Vulkan:     return CreateRef<VulkanIndexBuffer>(indices, size);
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}