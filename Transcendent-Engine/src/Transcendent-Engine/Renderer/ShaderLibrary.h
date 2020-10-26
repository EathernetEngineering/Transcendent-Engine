#pragma once

#include "Transcendent-Engine/Renderer/Shader.h"

#include <unordered_map>

namespace TE {

	class ShaderLibrary
	{
	public:
		static void Init();
		static void Shutdown();

		static void BindShader(const std::string& Name);
		static void BindShader(uint32_t ID);
		static void UnbindShader(const std::string& Name);
		static void UnbindShader(uint32_t ID);

		static void Add(const std::string& Filepath, const std::string& Name);
		static void Add(const ShaderSource& Source, const std::string& Name);
		static void Remove(std::string& Name);
		static void Remove(uint32_t ID);

		static uint32_t GetID(std::string& Name);
		static std::string  GetName(uint32_t ID);
		static Ref<Shader> GetShader(const std::string& Name);
		static Ref<Shader> GetShader(uint32_t ID);

	private:
		static std::unordered_map<std::string, Ref<Shader>> m_Shaders;
		static std::unordered_map<std::string, uint32_t> m_IDs;
		static std::unordered_map<uint32_t, std::string> m_Names;
	};
}
