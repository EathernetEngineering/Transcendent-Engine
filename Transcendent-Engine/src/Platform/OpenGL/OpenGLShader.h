#pragma once

#include <glm/glm.hpp>
#include "Transcendent-Engine/Renderer/Shader.h"

namespace TE {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& Filepath, const std::string& Name);
		OpenGLShader(const ShaderSource& Source, const std::string& Name);

		~OpenGLShader();

		void Bind()   override;
		void Unbind() override;

		std::string GetName() { return m_Name; }
		uint32_t GetID() { return m_ID; }

		void SetUniform    (const std::string& Name, int i0)                                    override;
		void SetUniform    (const std::string& Name, float i0)                                  override;
		void SetUniform    (const std::string& Name, glm::mat4 i0)                              override;
		void SetUniform    (const std::string& Name, int i0, int i1)                            override;
		void SetUniform    (const std::string& Name, float i0, float i1)                        override;
		void SetUniform    (const std::string& Name, int i0, int i1, int i2)                    override;
		void SetUniform    (const std::string& Name, float i0, float i1, float i2)              override;
		void SetUniform    (const std::string& Name, int i0, int i1, int i2, int i3)            override;
		void SetUniform    (const std::string& Name, float i0, float i1, float i2, float i3)    override;

		void SetIntArray(const std::string& Name, int* Data, size_t Count) override {}

	private:
		uint32_t GetUniformLocation(const std::string& Name);
		uint32_t CompileShader(const ShaderSource& Source) override;

	private:
		std::unordered_map<std::string, GLuint> m_UniformLocationCache;
		uint32_t m_ID;
		std::string m_Name;
	};
}
