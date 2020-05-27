#pragma once

#include "Transcendent-Engine/Renderer/Shader.h"

#include <unordered_map>

namespace TE {

	class ShaderLibrary
	{
	public:
		static void Init();
		static void Shutdown();

		static void BindShader(std::string& Name);
		static void BindShader(const char* Name);
		static void BindShader(unsigned int ID);
		static void UnbindShader(std::string& Name);
		static void UnbindShader(const char* Name);
		static void UnbindShader(unsigned int ID);

		static void Add(const std::string& Filepath, const std::string& Name);
		static void Add(const char* Filepath, const char* Name);
		static void Add(const std::string& VertexSource, const std::string& FragmentSource, const std::string& Name);
		static void Add(const char* VertexSource, const char* FragmentSource, const char* Name);
		static void Remove(std::string& Name);
		static void Remove(const char* Name);
		static void Remove(uint16_t ID);

		static unsigned int GetID(std::string& Name);
		static unsigned int GetID(const char* Name);
		static std::string  GetName(unsigned int ID);
		static Ref<Shader> GetShader(std::string& Name);
		static Ref<Shader> GetShader(const char* Name);
		static Ref<Shader> GetShader(unsigned int ID);

	private:
		static std::unordered_map<std::string, Ref<Shader>> m_Shaders;
		static std::unordered_map<std::string, uint16_t> m_IDs;
		static std::unordered_map<uint16_t, std::string> m_Names;
	};
}
