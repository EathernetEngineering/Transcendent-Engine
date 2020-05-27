#pragma once

#include "Transcendent-Engine/Renderer/OrthographicCamera.h"

namespace TE {

	class Renderer2D
	{
	public:

		static void Init();
		static void Shutdown(OrthographicCamera& camaera) {};

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene() {};

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		//static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4c& color);
		//static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4c& color);
	};
}