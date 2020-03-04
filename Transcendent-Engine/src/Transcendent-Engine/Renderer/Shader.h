#pragma once

#include <glm/glm.hpp>

#include <glad/glad.h>

namespace TE {

	class Shader
	{
	public:
		Shader(const std::string& Filepath, const std::string& Name);
		Shader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& Name);
		virtual ~Shader();

		virtual void Bind();
		virtual void Unbind();

		virtual void Create();

		// T and C will be deduced by the compiler
		virtual void SetUniform();
		virtual void SetUniform    (std::string& Name, int i0);
		virtual void SetUniform    (std::string& Name, float i0);
		virtual void SetUniform    (std::string& Name, glm::mat4 i0);
		virtual void SetUniform    (std::string& Name, int i0, int i1);
		virtual void SetUniform    (std::string& Name, float i0, float i1);
		virtual void SetUniform    (std::string& Name, int i0, int i1, int i2);
		virtual void SetUniform    (std::string& Name, float i0, float i1, float i2);
		virtual void SetUniform    (std::string& Name, int i0, int i1, int i2, int i3);
		virtual void SetUniform    (std::string& Name, float i0, float i1, float i2, float i3);


	public:
		struct ShaderSource
		{
			const std::string Vertex, Fragment;

			ShaderSource(std::string& Vertex, std::string& Fragment)
				: Vertex(Vertex), Fragment(Fragment)
			{
			}
		};

	private:
		virtual ShaderSource ParseShader(const std::string& Filepath);
		virtual unsigned int CompileShader(const std::string& VertexSource, const std::string& FragmentSource);
		virtual unsigned int CompileShader(const ShaderSource& Source);
		virtual unsigned int GetUniformLocation(std::string& Name);

	private:
		const std::string m_Name;
		const std::string m_Filepath = "";
		const std::string m_VertexSource;
		const std::string m_FragmentSource;
		Shader* m_Instance;
		Shader* m_ShaderAPI;
	};
}
