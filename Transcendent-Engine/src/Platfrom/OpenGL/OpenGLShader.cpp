#include "tepch.h"
#include "Platfrom/OpenGL/OpenGLShader.h"

namespace TE {

	OpenGLShader::OpenGLShader(const std::string& Filepath, const std::string& Name) {

		;
	}

	OpenGLShader::OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& Name) {

		;
	}

	OpenGLShader::~OpenGLShader() {

		
	}

	void OpenGLShader::Bind() {

		
	}

	void OpenGLShader::Unbind() {

		
	}

	void OpenGLShader::ParseShader(const std::string& Filepath) {

		
	}

	void OpenGLShader::CompileShader(const std::string& VertexSource, const std::string& FragmnetSource) {

		
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
