#include "tepch.h"
#include "Transcendent-Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace TE {

	void Renderer::Init() {

		RenderCommand::Init();
	}

	void Renderer::Shutdown() {

		;
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {

		RenderCommand::SetViewport(0, 0, width, height);
	}
}
