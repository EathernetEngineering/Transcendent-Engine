#include "tepch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

namespace TE {

	OpenGLShader::OpenGLShader(const std::string& Filepath, const std::string& Name) 
		: Shader(Filepath, Name), m_Filepath(Filepath), m_Name(Name), m_Instance(this),
		  m_VertexSource("INVALID!"), m_FragmentSource("INVALID!")
	{
	}

	OpenGLShader::OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& Name) 
		: Shader(VertexSource, FragmentSource, Name), m_Filepath("INVALID!"), m_Name(Name), m_Instance(this),
		  m_VertexSource(VertexSource), m_FragmentSource(FragmentSource)
	{
	}

	OpenGLShader::~OpenGLShader() {

		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Create() {
		if (m_Filepath != "INVALID!")
			m_ID = this->CompileShader(this->ParseShader(m_Filepath));
		else if (m_VertexSource != "INVALID!" && m_FragmentSource != "INVALID!")
			m_ID = this->CompileShader(m_VertexSource, m_FragmentSource);
		else
			TE_CORE_ASSERT(false, "Shader filepath or source not provided!");
	}

	void OpenGLShader::Bind() {

		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() {

		glUseProgram(0u);
	}

	Shader::ShaderSource OpenGLShader::ParseShader(const std::string& Filepath) {

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		};

		std::basic_fstream<char, std::char_traits<char>> stream(Filepath, std::ios_base::in);
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line)) {

			if ((line.find("#shader vertex") != std::string::npos) || (line.find("#type vertex") != std::string::npos))
				type = ShaderType::VERTEX;
			else if ((line.find("#shader fragment") != std::string::npos) || (line.find("#type fragment") != std::string::npos) ||
				(line.find("#shader pixel") != std::string::npos) || (line.find("#type pixel") != std::string::npos))
				type = ShaderType::FRAGMENT;
			else
				ss[(int)type] << line << std::endl;
		}

		return { ss[0].str(), ss[1].str() };
	}

	GLuint OpenGLShader::CompileShader(const ShaderSource& Source) {

		return this->CompileShader(Source.Vertex, Source.Fragment);
	}

	GLuint OpenGLShader::CompileShader(const std::string& VertexSource, const std::string& FragmentSource) {

		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		 
		GLint Result = GL_FALSE;
		int InfoLogLength;

		
		char const* VertexSourcePointer = VertexSource.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);
		
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<GLchar> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			TE_CORE_ERROR("{0}", VertexShaderErrorMessage.data());
			TE_CORE_ASSERT(false, "Shader compilation failure!");
		} 
		else TE_CORE_INFO("Compiled vertex shader");

		
		char const* FragmentSourcePointer = FragmentSource.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			TE_CORE_ERROR("{0}", FragmentShaderErrorMessage.data());
			TE_CORE_ASSERT(false, "Shader compilation failure!");
		} 
		else TE_CORE_INFO("Compiled fragment shader");

		// Link the program
		
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			TE_CORE_ERROR("{0}", ProgramErrorMessage.data());
			TE_CORE_ASSERT(false, "Shader linking failure!");
		}
		else TE_CORE_INFO("Linked Shader");

		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return ProgramID;
	}

	GLuint OpenGLShader::GetUniformLocation(const std::string& Name) {

		if (m_UniformLocations.find(Name) != m_UniformLocations.end())
			return m_UniformLocations[Name];

		int location = glad_glGetUniformLocation(m_ID, Name.c_str());
		if (location == -1) {
			TE_CORE_WARN("Uniform {0} doesn't exist!", Name);
			return INT_MAX;
		}

		m_UniformLocations[Name] = location;

		return location;
	}

	void OpenGLShader::SetUniform() {

		TE_CORE_ASSERT(false, "Data must be provided to template")
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, int i0) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniform1i(this->GetUniformLocation(Name), i0);
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, int i0, int i1) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniform2i(this->GetUniformLocation(Name), i0, i1);
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, int i0, int i1, int i2) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniform3i(this->GetUniformLocation(Name), i0, i1, i2);
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, int i0, int i1, int i2, int i3) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniform4i(this->GetUniformLocation(Name), i0, i1, i2, i3);
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, float i0) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniform1f(this->GetUniformLocation(Name), i0);
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, float i0, float i1) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniform2f(this->GetUniformLocation(Name), i0, i1);
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, float i0, float i1, float i2) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniform3f(this->GetUniformLocation(Name), i0, i1, i2);
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, float i0, float i1, float i2, float i3) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniform4f(this->GetUniformLocation(Name), i0, i1, i2, i3);
	}

	
	void OpenGLShader::SetUniform(const std::string& Name, glm::mat4 i0) {

		if (this->GetUniformLocation(Name) == INT_MAX) {
			TE_CORE_ERROR("{0} Does not exist!", Name);
			return;
		}

		glUniformMatrix4fv(this->GetUniformLocation(Name), 1, GL_FALSE, &i0[0][0]);
	}
}
