#include "tepch.h"
#include "SandboxLayer.h"
#include "imgui/imgui.h"

#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <gl/GL.h>

SandboxLayer::SandboxLayer() {


}

void SandboxLayer::OnAttach() {

	std::string test, vertex, fragment;
	test = "name";

	vertex   = "#version 410\n"
			   "layout(location = 0) in vec4 VertexPosition;\n"
			   "void main() {\n"
			   "	gl_Position = VertexPosition;\n"
			   "}\n";

	fragment = "#version 410\n" 
			   "out vec3 color;\n" 
			   "void main() {\n" 
			   "	color = vec3(1, 0, 0);\n" 
			   "}\n";

	m_shader = TE::CreateRef<TE::Shader>(vertex, fragment, test);
	
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

	
}

SandboxLayer::~SandboxLayer() {


}
