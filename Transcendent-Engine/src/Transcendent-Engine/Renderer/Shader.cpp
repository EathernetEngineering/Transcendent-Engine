#include "tepch.h"
#include "Transcendent-Engine/Renderer/Shader.h"

#include "Transcendent-Engine/Renderer/RendererAPI.h"

#include "Platfrom/OpenGL/OpenGLShader.h"

namespace TE {

	Shader::Shader(const std::string& Filepath, const std::string& Name) 
		: m_Instance(this), m_ShaderAPI(nullptr), m_Filepath(Filepath), m_Name(Name)
	{
	}

	Shader::Shader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& Name) 
		: m_Instance(this), m_ShaderAPI(nullptr), m_VertexSource(VertexSource), m_FragmentSource(FragmentSource)
	{
	}

	Shader::~Shader() {

		delete m_ShaderAPI;
	}

	void Shader::Create() {

		switch (RendererAPI::GetAPI()) {

		case RendererAPI::API::OpenGL:
		{
			if (m_Filepath != "")
				m_ShaderAPI = new OpenGLShader(m_Filepath, m_Name);
			else
				m_ShaderAPI = new OpenGLShader(m_VertexSource, m_FragmentSource, m_Name);

			m_ShaderAPI->Create();
		}
		break;

		default:
			TE_CORE_ASSERT(false, "Unknown Renderer API");
		}
	}

	void Shader::Bind() {

		m_ShaderAPI->Bind();
	}

	void Shader::Unbind() {

		m_ShaderAPI->Unbind();
	}

	Shader::ShaderSource Shader::ParseShader(const std::string& Filepath) {

		m_ShaderAPI->ParseShader(Filepath);
		std::string str[2];
		str[0] = "1";
		str[1] = "1";
		return { str[0], str[1] };
	}

	GLuint Shader::CompileShader(const ShaderSource& Source) {

		return m_ShaderAPI->CompileShader(Source);
	}

	GLuint Shader::CompileShader(const std::string& VertexSource, const std::string& FragmentSource) {

		return m_ShaderAPI->CompileShader(VertexSource, FragmentSource);
	}

	GLuint Shader::GetUniformLocation() {

		m_ShaderAPI->GetUniformLocation();
		return 0;
	}
	
	void Shader::SetUniform() {

		TE_CORE_ASSERT(false, "Data must be provided to template")
	}

	
	void Shader::SetUniform(int i0) {

		m_ShaderAPI->SetUniform(i0);
	}

	
	void Shader::SetUniform(int i0, int i1) {

		m_ShaderAPI->SetUniform(i0, i1);
	}

	
	void Shader::SetUniform(int i0, int i1, int i2) {

		m_ShaderAPI->SetUniform(i0, i1, i2);
	}

	
	void Shader::SetUniform(int i0, int i1, int i2, int i3) {

		m_ShaderAPI->SetUniform(i0, i1, i2, i3);
	}

	
	void Shader::SetUniform(float i0) {

		m_ShaderAPI->SetUniform(i0);
	}

	
	void Shader::SetUniform(float i0, float i1) {

		m_ShaderAPI->SetUniform(i0, i1);
	}

	
	void Shader::SetUniform(float i0, float i1, float i2) {

		m_ShaderAPI->SetUniform(i0, i1, i2);
	}

	
	void Shader::SetUniform(float i0, float i1, float i2, float i3) {

		m_ShaderAPI->SetUniform(i0, i1, i2, i3);
	}

	
	void Shader::SetUniform(glm::mat4 i0) {

		m_ShaderAPI->SetUniform(i0);
	}

	
	void Shader::SetUniform(glm::vec2 i0) {

		m_ShaderAPI->SetUniform(i0);
	}

	
	void Shader::SetUniform(glm::vec3 i0) {

		m_ShaderAPI->SetUniform(i0);
	}

	
	void Shader::SetUniform(glm::vec4 i0) {

		m_ShaderAPI->SetUniform(i0);
	}
}
