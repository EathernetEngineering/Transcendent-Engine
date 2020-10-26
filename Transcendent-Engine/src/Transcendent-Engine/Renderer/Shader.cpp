#include "tepch.h"
#include "Transcendent-Engine/Renderer/Shader.h"

#include "Transcendent-Engine/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/Vulkan/VulkanShader.h"

namespace TE {

	Scope<Shader> Shader::Create(const std::string& Filepath, const std::string& Name) {

		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::NONE:       TE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
			case RendererAPI::API::DirectX12:  TE_CORE_ASSERT(false, "RendererAPI::DirectX12 is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:     return CreateScope<VulkanShader>(Filepath, Name);
			case RendererAPI::API::Vulkan:     return CreateScope<VulkanShader>(Filepath, Name);
			default:                           TE_CORE_ASSERT(false, "Unknown Renderer API"); return nullptr;
		}
	}
	
	Scope<Shader> Shader::Create(const ShaderSource& Source, const std::string& Name) {

		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::NONE:       TE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
			case RendererAPI::API::DirectX12:  TE_CORE_ASSERT(false, "RendererAPI::DirectX12 is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:     return CreateScope<VulkanShader>(Source, Name);
			case RendererAPI::API::Vulkan:     return CreateScope<VulkanShader>(Source, Name);
			default:                           TE_CORE_ASSERT(false, "Unknown Renderer API"); return nullptr;
		}
	}

	ShaderSource Shader::ParseShader(const std::string& Filepath) {

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

}
