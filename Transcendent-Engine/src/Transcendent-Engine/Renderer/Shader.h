#pragma once

#include <glm/glm.hpp>

#include <glad/glad.h>

namespace TE {

	struct ShaderSource
	{
		const std::string Vertex, Fragment;

		ShaderSource(const std::string& Vertec, const std::string& Fragment)
			: Vertex(Vertex), Fragment(Fragment)
		{
		}
	};

	class Shader
	{
	public:
		Shader() {}
		virtual ~Shader() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Scope<Shader> Create(const std::string& Filepath, const std::string& Name);
		static Scope<Shader> Create(const ShaderSource& Source,  const std::string& Name);

		virtual std::string GetName() = 0;
		virtual uint32_t    GetID() = 0;

		virtual void SetUniform (const std::string& Name, int i0) = 0;
		virtual void SetUniform (const std::string& Name, float i0) = 0;
		virtual void SetUniform (const std::string& Name, glm::mat4 i0) = 0;
		virtual void SetUniform (const std::string& Name, int i0, int i1) = 0;
		virtual void SetUniform (const std::string& Name, float i0, float i1) = 0;
		virtual void SetUniform (const std::string& Name, int i0, int i1, int i2) = 0;
		virtual void SetUniform (const std::string& Name, float i0, float i1, float i2) = 0;
		virtual void SetUniform (const std::string& Name, int i0, int i1, int i2, int i3) = 0;
		virtual void SetUniform (const std::string& Name, float i0, float i1, float i2, float i3) = 0;

		virtual void SetIntArray(const std::string& Name, int* Data, size_t Count) = 0;

	private:
		ShaderSource ParseShader(const std::string& Filepath);
		virtual uint32_t CompileShader(const ShaderSource& Source) = 0;
		virtual uint32_t GetUniformLocation(std::string& Name) = 0;
	};
}
