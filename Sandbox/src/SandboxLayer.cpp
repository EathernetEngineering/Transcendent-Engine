#include "tepch.h"
#include "SandboxLayer.h"
#include "imgui/imgui.h"
#include <unordered_map>
#include <Transcendent-Engine/core/core.h>

#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <gl/GL.h>

#include <glm/gtc/type_ptr.hpp>

SandboxLayer::SandboxLayer() {

	
}

void SandboxLayer::OnAttach() {
	m_Position1 = { 200.0f, 200.0f };
	m_Scale1 = { 100.0f,100.0f };
	m_Colour1 = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_Position2 = { 800.0f, 200.0f };
	m_Scale2 = { 100.0f,100.0f };
	m_Colour2 = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_Position3 = { 200.0f, 200.0f };
	m_Scale3 = { 100.0f,100.0f };
	m_Colour3 = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_Position4 = { 800.0f, 200.0f };
	m_Scale4 = { 100.0f,100.0f };
	m_Colour4 = { 1.0f, 1.0f, 1.0f, 1.0f };

	//m_spec = new TE::FrameBufferSpecification();
	//m_spec->Width = 1280;
	//m_spec->Height = 720;
	//m_FrameBufferObject = TE::FrameBuffer::Create(*m_spec);
}

void SandboxLayer::OnDetach() {

	
}

void SandboxLayer::OnUpdate() {

	//m_FrameBufferObject->Bind();
	TE::Renderer2D::BeginScene(*m_Camera);
	TE::Renderer2D::DrawQuad(m_Position1, m_Scale1, m_Colour1);
	TE::Renderer2D::DrawQuad(m_Position2, m_Scale2, m_Colour2);
	TE::Renderer2D::DrawQuad(m_Position3, m_Scale3, m_Colour3);
	TE::Renderer2D::DrawQuad(m_Position4, m_Scale4, m_Colour4);
	TE::Renderer2D::EndScene();
	//m_FrameBufferObject->Unbind();
}

void SandboxLayer::OnImGuiRender() {

	//ImGui::Begin("Box Colour");
	//ImGui::ColorEdit4("Colour 1", &m_Colour1[0]);
	//ImGui::ColorEdit4("Colour 2", &m_Colour2[0]);
	//ImGui::ColorEdit4("Colour 3", &m_Colour3[0]);
	//ImGui::ColorEdit4("Colour 4", &m_Colour4[0]);
	//ImGui::End();
	//
	//ImGui::Begin("Box Tranforms");
	//ImGui::SliderFloat("Box 1 Tranform X", &m_pos1[0], 0.0f, 1180.0f);
	//ImGui::SliderFloat("Box 1 Tranform Y", &m_pos1[1], 0.0f, 620.0f);
	//ImGui::SliderFloat("Box 2 Tranform X", &m_pos2[0], 0.0f, 1180.0f);
	//ImGui::SliderFloat("Box 2 Tranform Y", &m_pos2[1], 0.0f, 620.0f);
	//ImGui::SliderFloat("Box 3 Tranform X", &m_pos3[0], 0.0f, 1180.0f);
	//ImGui::SliderFloat("Box 3 Tranform Y", &m_pos3[1], 0.0f, 620.0f);
	//ImGui::SliderFloat("Box 4 Tranform X", &m_pos4[0], 0.0f, 1180.0f);
	//ImGui::SliderFloat("Box 4 Tranform Y", &m_pos4[1], 0.0f, 620.0f);
	//ImGui::SliderFloat("Box 1 Scale", &m_Scalef1, 50.0f, 500.0f);
	//ImGui::SliderFloat("Box 2 Scale", &m_Scalef2, 50.0f, 500.0f);
	//ImGui::SliderFloat("Box 3 Scale", &m_Scalef3, 50.0f, 500.0f);
	//ImGui::SliderFloat("Box 4 Scale", &m_Scalef4, 50.0f, 500.0f);
	//ImGui::End();
	//
	//m_Position1.x = m_pos1[0] + 50.0f;
	//m_Position1.y = m_pos1[1] + 50.0f;
	//m_Position2.x = m_pos2[0] + 50.0f;
	//m_Position2.y = m_pos2[1] + 50.0f;
	//m_Position3.x = m_pos3[0] + 50.0f;
	//m_Position3.y = m_pos3[1] + 50.0f;
	//m_Position4.x = m_pos4[0] + 50.0f;
	//m_Position4.y = m_pos4[1] + 50.0f;
	//	
	//m_Colour1 = { m_Colour1[0], m_Colour1[1], m_Colour1[2], m_Colour1[3] };
	//m_Colour2 = { m_Colour2[0], m_Colour2[1], m_Colour2[2], m_Colour2[3] };
	//m_Colour3 = { m_Colour3[0], m_Colour3[1], m_Colour3[2], m_Colour2[3] };
	//m_Colour4 = { m_Colour4[0], m_Colour4[1], m_Colour4[2], m_Colour3[3] };
	//
	//m_Scale1 = { m_Scalef1, m_Scalef1 };
	//m_Scale2 = { m_Scalef2, m_Scalef2 };
	//m_Scale3 = { m_Scalef3, m_Scalef3 };
	//m_Scale4 = { m_Scalef4, m_Scalef4 };
	//
	//ImGui::Begin("Scene");
	////m_spec->Width  = ImGui::GetContentRegionAvail().x;
	////m_spec->Height = ImGui::GetContentRegionAvail().y;
	////m_FrameBufferObject->UpdateSpecification(*m_spec);
	//ImGui::Image((void*)m_FrameBufferObject->GetColourAttachmentRendererID(), ImVec2(m_spec->Width, m_spec->Height));
	//ImGui::End();
}

SandboxLayer::~SandboxLayer() {


}
