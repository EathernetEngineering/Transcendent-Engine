#include "tepch.h"
#include "SandboxLayer.h"
#include "imgui/imgui.h"

#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <gl/GL.h>

SandboxLayer::SandboxLayer() {


}

void SandboxLayer::OnAttach() {

	std::string Name, vertex, fragment;
	Name = "name";

	vertex   = "#version 410\n\n"
			   "layout(location = 0) in vec4 VertexPosition;\n\n"
			   "void main() {\n\n"
			   "	gl_Position = VertexPosition;\n"
			   "}\n";

	fragment = "#version 410\n\n" 
			   "layout(location = 0) out vec4 color;\n\n" 
			   "uniform vec4 u_Colour;\n\n"
			   "void main() {\n\n" 
			   "	color = u_Colour;\n" 
			   "}\n";

	m_shader = TE::CreateRef<TE::Shader>(vertex, fragment, Name);
	
	m_shader->Create();
	m_shader->Bind();

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

	

	m_shader->Bind();
	m_VAO->Bind();
	m_IndexBuffer->Bind();
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void SandboxLayer::OnImGuiRender() {

	ImGui::Begin("Box Colour");
	ImGui::ColorEdit4("Colour", &m_Colour[0]);
	ImGui::End();

	m_shader->Bind();
	m_shader->SetUniform(std::string("u_Colour"), m_Colour[0], m_Colour[1], m_Colour[2], m_Colour[3]);
}

SandboxLayer::~SandboxLayer() {


}
