#pragma once

#include "Transcendent-Engine/Renderer/OrthographicCamera.h"

namespace TE {

	class Renderer2D
	{
	public:

		static void Init();
		static void Shutdown() {};

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		//static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4c& color);
		//static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4c& color);

		typedef struct {
			uint64_t DrawCalls;
			uint64_t QuadCount;
			uint64_t GetTotalVertexCount() const { return QuadCount * (uint64_t)4; }
			uint64_t GetTotalIndexCount() const { return QuadCount * (uint64_t)6; }
		} Statistics;

		static void Flush();

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void StartBatch();
		static void NextBatch();
	};
}