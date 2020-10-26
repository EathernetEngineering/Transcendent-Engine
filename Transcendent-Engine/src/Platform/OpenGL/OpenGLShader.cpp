#include "tepch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

namespace TE {

	OpenGLShader::OpenGLShader(const std::string& Filepath, const std::string& Name) 
		: m_Name(Name), m_ID((uint32_t)-1)
	{
	}

	OpenGLShader::OpenGLShader(const ShaderSource& Source, const std::string& Name) 
		: m_Name(Name), m_ID((uint32_t)-1)
	{
	}

	OpenGLShader::~OpenGLShader() {

		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Bind() {

		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() {

		glUseProgram(0u);
	}

	uint32_t OpenGLShader::CompileShader(const ShaderSource& Source) {

		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		 
		GLint Result = GL_FALSE;
		int InfoLogLength;

		
		char const* VertexSourcePointer = Source.Vertex.c_str();
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

		
		char const* FragmentSourcePointer = Source.Fragment.c_str();
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

		if (m_UniformLocationCache.find(Name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[Name];

		int location = glad_glGetUniformLocation(m_ID, Name.c_str());
		if (location == -1) {
			TE_CORE_WARN("Uniform {0} doesn't exist!", Name);
			return INT_MAX;
		}

		m_UniformLocationCache[Name] = location;

		return location;
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
