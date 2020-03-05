#include "tepch.h"
#include "SandboxLayer.h"
#include "imgui/imgui.h"
#include <unordered_map>
#include <Transcendent-Engine/core/core.h>

#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <gl/GL.h>

SandboxLayer::SandboxLayer() {


}

void SandboxLayer::OnAttach() {

	TE::ShaderLibrary::BindShader(std::string("Colour"));

	float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VAO = TE::CreateRef<TE::VertexArray>();
	TE::VertexArray va;
	m_VertexBuffer = std::make_unique<TE::VertexBuffer>(positions, 4 * 2 * sizeof(float));
	TE::VertexBufferLayout layout;
	layout.Push<float>(2);
	m_VAO->addBuffer(*m_VertexBuffer, layout);
	m_IndexBuffer = std::make_unique<TE::IndexBuffer>(indices, 6);
}

void SandboxLayer::OnDetach() {

	
}

void SandboxLayer::OnUpdate() {

	

	TE::ShaderLibrary::BindShader(std::string("Colour"));
	m_VAO->Bind();
	m_IndexBuffer->Bind();
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void SandboxLayer::OnImGuiRender() {

	ImGui::Begin("Box Colour");
	ImGui::ColorEdit4("Colour", &m_Colour[0]);
	ImGui::End();

	TE::ShaderLibrary::GetShader(std::string("Colour"))->Bind();
	TE::ShaderLibrary::GetShader(std::string("Colour"))->SetUniform(std::string("u_Colour"), m_Colour[0], m_Colour[1], m_Colour[2], m_Colour[3]);
}

SandboxLayer::~SandboxLayer() {


}
