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

		std::string GetName() { return m_Name; }
		unsigned int GetID() { return m_ID; }

		void SetUniform    ()															  override;
		void SetUniform    (const std::string& Name, int i0)                                    override;
		void SetUniform    (const std::string& Name, float i0)                                  override;
		void SetUniform    (const std::string& Name, glm::mat4 i0)                              override;
		void SetUniform    (const std::string& Name, int i0, int i1)                            override;
		void SetUniform    (const std::string& Name, float i0, float i1)                        override;
		void SetUniform    (const std::string& Name, int i0, int i1, int i2)                    override;
		void SetUniform    (const std::string& Name, float i0, float i1, float i2)              override;
		void SetUniform    (const std::string& Name, int i0, int i1, int i2, int i3)            override;
		void SetUniform    (const std::string& Name, float i0, float i1, float i2, float i3)    override;


	private:
		ShaderSource ParseShader(const std::string& Filepath) override;
		GLuint GetUniformLocation(const std::string& Name);
		GLuint CompileShader(const std::string& VertexShader, const std::string& FragmentShader) override;
		GLuint CompileShader(const ShaderSource& Source) override;

	private:
		std::unordered_map<std::string, GLuint> m_UniformLocations;
		unsigned int m_ID;
		std::string m_Filepath, m_Name, m_VertexSource, m_FragmentSource;
		Shader* m_Instance;
	};
}
