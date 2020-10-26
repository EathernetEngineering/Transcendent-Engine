#pragma once

#include <Transcendent-Engine/Renderer/Shader.h>

namespace TE {

	class VulkanShader : public Shader
	{
	public:
		VulkanShader(const std::string& Filepath, const std::string& Name) {}
		VulkanShader(const ShaderSource& Source, const std::string& Name) {}

		void Bind() override {}
		void Unbind() override {}

		std::string GetName() { return ""; }
		uint32_t    GetID() { return (uint32_t)-1; }

		void SetUniform(const std::string& Name, int i0) {}
		void SetUniform(const std::string& Name, float i0) {}
		void SetUniform(const std::string& Name, glm::mat4 i0) {}
		void SetUniform(const std::string& Name, int i0, int i1) {}
		void SetUniform(const std::string& Name, float i0, float i1) {}
		void SetUniform(const std::string& Name, int i0, int i1, int i2) {}
		void SetUniform(const std::string& Name, float i0, float i1, float i2) {}
		void SetUniform(const std::string& Name, int i0, int i1, int i2, int i3) {}
		void SetUniform(const std::string& Name, float i0, float i1, float i2, float i3) {}

		void SetIntArray(const std::string& Name, int* Data, size_t Count) override {}

	private:
		uint32_t CompileShader(const ShaderSource& Source) { return (uint32_t)-1; }
		uint32_t GetUniformLocation(std::string& Name) { return (uint32_t)-1; }
	};

}
