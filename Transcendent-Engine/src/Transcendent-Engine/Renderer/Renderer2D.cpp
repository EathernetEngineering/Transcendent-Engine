#include "tepch.h"
#include "Transcendent-Engine/Renderer/Renderer2D.h"

#include "Transcendent-Engine/Renderer/OrthographicCamera.h"

#include "Transcendent-Engine/Renderer/RenderCommand.h"
#include "Transcendent-Engine/Renderer/Shader.h"
#include "Transcendent-Engine/Renderer/ShaderLibrary.h"
#include "Transcendent-Engine/Renderer/Texture.h"

#include <glm/gtc/matrix_transform.hpp>

namespace TE {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Shader> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {

		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->WhiteTexture = ShaderLibrary::GetShader("Colour");
		s_Data->TextureShader = ShaderLibrary::GetShader("Texture");
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data->WhiteTexture->Bind();
		s_Data->WhiteTexture->SetUniform("u_ViewProjection", camera.GetViewProjectionMatrix());
		
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetUniform("u_ViewProjection", camera.GetViewProjectionMatrix());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

		s_Data->WhiteTexture->Bind();
		s_Data->WhiteTexture->SetUniform(std::string("u_Colour"), color.r, color.g, color.b, color.a);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->WhiteTexture->SetUniform(std::string("u_Transform"), transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}
