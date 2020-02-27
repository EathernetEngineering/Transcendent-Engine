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
			TE_CORE_ASSERT(false, "Unknown Renderer API")
		}
	}

	void Shader::Bind() {

		m_ShaderAPI->Bind();
	}

	void Shader::Unbind() {

		m_ShaderAPI->Unbind();
	}

	void Shader::ParseShader(const std::string& Filepath) {

		m_ShaderAPI->ParseShader(Filepath);
	}

	void Shader::CompileShader(const std::string& VertexSource, const std::string& FragmnetSource) {

		m_ShaderAPI->CompileShader(VertexSource, FragmnetSource);
	}

	
	void Shader::SetUniform() {

		TE_CORE_ASSERT(false, "Data must be provided to template")
	}

	
	void Shader::SetUniform(int i0) {


	}

	
	void Shader::SetUniform(int i0, int i1) {

	}

	
	void Shader::SetUniform(int i0, int i1, int i2) {


	}

	
	void Shader::SetUniform(int i0, int i1, int i2, int i3) {


	}

	
	void Shader::SetUniform(float i0) {


	}

	
	void Shader::SetUniform(float i0, float i1) {


	}

	
	void Shader::SetUniform(float i0, float i1, float i2) {


	}

	
	void Shader::SetUniform(float i0, float i1, float i2, float i3) {


	}

	
	void Shader::SetUniform(glm::mat4 i0) {


	}

	
	void Shader::SetUniform(glm::vec2 i0) {


	}

	
	void Shader::SetUniform(glm::vec3 i0) {


	}

	
	void Shader::SetUniform(glm::vec4 i0) {


	}
}
