#include "tepch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace TE {

	void OpenGLMessageCallback(
		uint32_t source,
		uint32_t type,
		uint32_t id,
		uint32_t severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         TE_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       TE_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          TE_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: TE_CORE_TRACE(message); return;
		}

		TE_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init() {

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {

		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, size_t Count)
	{
		size_t count;
		Count == 0 ? count = vertexArray->GetIndexBuffer()->GetCount() : count = Count;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLRendererAPI::BeginScene()
	{

	}

	void OpenGLRendererAPI::EndScene()
	{

	}
}
