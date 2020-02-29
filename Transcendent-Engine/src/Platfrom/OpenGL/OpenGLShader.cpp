#include "tepch.h"
#include "Platfrom/OpenGL/OpenGLShader.h"

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

namespace TE {

	OpenGLShader::OpenGLShader(const std::string& Filepath, const std::string& Name) 
		: Shader(Filepath, Name)
	{

		m_ID = this->CompileShader(this->ParseShader(Filepath));
	}

	OpenGLShader::OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& Name) 
		: Shader(VertexSource, FragmentSource, Name) 
	{

		m_ID = this->CompileShader(VertexSource, FragmentSource);
	}

	OpenGLShader::~OpenGLShader() {

		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Create() {

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

		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return ProgramID;
	}

	void OpenGLShader::SetUniform() {

		TE_CORE_ASSERT(false, "Data must be provided to template")
	}

	
	void OpenGLShader::SetUniform(int i0) {

		
	}

	
	void OpenGLShader::SetUniform(int i0, int i1) {

		
	}

	
	void OpenGLShader::SetUniform(int i0, int i1, int i2) {

		
	}

	
	void OpenGLShader::SetUniform(int i0, int i1, int i2, int i3) {

		
	}

	
	void OpenGLShader::SetUniform(float i0) {

		
	}

	
	void OpenGLShader::SetUniform(float i0, float i1) {


	}

	
	void OpenGLShader::SetUniform(float i0, float i1, float i2) {


	}

	
	void OpenGLShader::SetUniform(float i0, float i1, float i2, float i3) {


	}

	
	void OpenGLShader::SetUniform(glm::mat4 i0) {


	}

	
	void OpenGLShader::SetUniform(glm::vec2 i0) {


	}

	
	void OpenGLShader::SetUniform(glm::vec3 i0) {


	}

	
	void OpenGLShader::SetUniform(glm::vec4 i0) {


	}
}
