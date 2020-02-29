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

	shader = TE::CreateRef<TE::Shader>(vertex, fragment, test);

	shader->Create();
	shader->Bind();
}

void SandboxLayer::OnDetach() {

	
}

void SandboxLayer::OnUpdate() {

	GLuint ElementBuffer;
	GLuint VertexBuffer;

	float verticies[]{

		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int Indexs[]{

		0, 1, 3,
		1, 2, 3
	};

	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), verticies, GL_STATIC_DRAW);
	glad_glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &Indexs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

void SandboxLayer::OnImGuiRender() {


}

SandboxLayer::~SandboxLayer() {


}
