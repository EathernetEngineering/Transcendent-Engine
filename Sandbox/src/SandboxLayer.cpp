#include "tepch.h"
#include "SandboxLayer.h"
#include "imgui/imgui.h"
#include <unordered_map>
#include <Transcendent-Engine/core/core.h>

#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <gl/GL.h>

SandboxLayer::SandboxLayer() {

	m_Position1 = { 200.0f, 200.0f };
	m_Scale1 = { 100.0f,100.0f };
	m_Colour1 = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	m_Position2 = { 800.0f, 200.0f };
	m_Scale2 = { 100.0f,100.0f };
	m_Colour2 = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void SandboxLayer::OnAttach() {

}

void SandboxLayer::OnDetach() {

	
}

void SandboxLayer::OnUpdate() {

	TE::Renderer2D::BeginScene(*m_Camera);
	TE::Renderer2D::DrawQuad(m_Position1, m_Scale1, m_Colour1);
	TE::Renderer2D::DrawQuad(m_Position2, m_Scale2, m_Colour2);
	TE::Renderer2D::EndScene();
}

void SandboxLayer::OnImGuiRender() {

	ImGui::Begin("Box Colour");
	ImGui::ColorEdit4("Colour 1", &m_Colour1[0]);
	ImGui::ColorEdit4("Colour 2", &m_Colour2[0]);
	ImGui::End();

	m_Colour1 = { m_Colour1[0], m_Colour1[1], m_Colour1[2], m_Colour1[3] };
	m_Colour2 = { m_Colour2[0], m_Colour2[1], m_Colour2[2], m_Colour2[3] };
}

SandboxLayer::~SandboxLayer() {


}
