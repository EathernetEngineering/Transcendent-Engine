#pragma once

#include "Transcendent-Engine/Renderer/RendererAPI.h"
#include "Platfrom/OpenGL/VertexArray.h"

namespace TE {

	class OpenGLRendererAPI : public RendererAPI
	{
		void Init();
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void SetClearColor(const glm::vec4& color);
		void Clear();
		void DrawIndexed(const Ref<VertexArray>& VertexArray);
	};
}
