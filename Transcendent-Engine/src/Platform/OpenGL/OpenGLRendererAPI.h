#pragma once

#include "Transcendent-Engine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace TE {

	class OpenGLRendererAPI : public RendererAPI
	{
		void Init() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void DrawIndexed(const Ref<VertexArray>& VertexArray, size_t Count) override;

		void BeginScene() override;
		void EndScene() override;
	};
}
