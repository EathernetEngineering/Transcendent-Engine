#pragma once

#include <glm/glm.hpp>
#include "Transcendent-Engine/Renderer/Shader.h"

namespace TE {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& Filepath, const std::string& Name);
		OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& Name);

		~OpenGLShader();

		void Bind()   override;
		void Unbind() override;

		void Create() override;

		// C will be deduced by the compiler
		void SetUniform    ()                                          override;
		void SetUniform    (int i0)                                    override;
		void SetUniform    (float i0)                                  override;
		void SetUniform    (glm::vec2 i0)                              override;
		void SetUniform    (glm::vec3 i0)                              override;
		void SetUniform    (glm::vec4 i0)                              override;
		void SetUniform    (glm::mat4 i0)                              override;
		void SetUniform    (int i0, int i1)                            override;
		void SetUniform    (float i0, float i1)                        override;
		void SetUniform    (int i0, int i1, int i2)                    override;
		void SetUniform    (float i0, float i1, float i2)              override;
		void SetUniform    (int i0, int i1, int i2, int i3)            override;
		void SetUniform    (float i0, float i1, float i2, float i3)    override;


	private:
		ShaderSource ParseShader(const std::string& Filepath) override;
		GLuint CompileShader(const std::string& VertexShader, const std::string& FragmentShader) override;
		GLuint CompileShader(const ShaderSource& Source) override;

	private:
		unsigned int m_ID;
		Shader* m_Instance;
	};
}
