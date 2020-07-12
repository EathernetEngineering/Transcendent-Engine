#include "tepch.h"
#include "ImGuiUILayer.h"
#include "imgui/imgui.h"

ImGuiUILayer::ImGuiUILayer(const std::string& DebugName)
	: m_DebugName(DebugName)
{

}

ImGuiUILayer::~ImGuiUILayer() 
{

}

void ImGuiUILayer::OnAttach() 
{
	m_Camera = new TE::OrthographicCamera(0.0f, 1280.0f, 720.0f, 0.0f);
	m_GameCamera = new TE::OrthographicCamera(0.0f, 1280.0f, 720.0f, 0.0f);
	m_Spec = new TE::FrameBufferSpecification();
	m_Spec->Width = 1280;
	m_Spec->Height =  720;
	m_FrameBufferObject = TE::FrameBuffer::Create(*m_Spec);
	m_GameFrameBufferObject = TE::FrameBuffer::Create(*m_Spec);
}

void ImGuiUILayer::OnDetach() 
{

}


void ImGuiUILayer::OnUpdate(TE::Timestep ts) 
{
	m_FrameBufferObject->Bind();
	TE::Renderer2D::BeginScene(*m_Camera);
	TE::Renderer2D::DrawQuad(glm::vec2(0, 0), glm::vec2(100, 100), glm::vec4(0.2f, 0.0f, 0.8f, 1.0f));
	TE::Renderer2D::EndScene();
	m_FrameBufferObject->Unbind();
	m_GameFrameBufferObject->Bind();
	TE::Renderer2D::BeginScene(*m_GameCamera);
	TE::Renderer2D::DrawQuad(glm::vec2(0, 0), glm::vec2(100, 100), glm::vec4(0.8f, 0.0f, 0.2, 1.0f));
	TE::Renderer2D::EndScene();
	m_GameFrameBufferObject->Unbind();
}

void ImGuiUILayer::OnImGuiRender() 
{
	ImGui::Begin("Scene", &m_SceneOpen);
	ImGui::Image((void*)m_FrameBufferObject->GetColourAttachmentRendererID(), { (float)m_Spec->Width, (float)m_Spec->Height });
	ImGui::End();
	ImGui::Begin("Game", &m_SceneOpen);
	ImGui::Image((void*)m_GameFrameBufferObject->GetColourAttachmentRendererID(), { (float)m_Spec->Width, (float)m_Spec->Height });
	ImGui::End();
}

void ImGuiUILayer::OnEvent(TE::Event& e) 
{

}
