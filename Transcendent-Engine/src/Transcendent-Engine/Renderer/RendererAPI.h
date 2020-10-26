#pragma once

#include <glm/glm.hpp>
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace TE {

	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0, OpenGL = 1, Vulkan = 2, DirectX12 = 3
		};

	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& VertexArray, size_t count) = 0;

		virtual void BeginScene() = 0;
		virtual void EndScene() = 0;

		inline static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();

	private:
		static API s_API;
	};
}
