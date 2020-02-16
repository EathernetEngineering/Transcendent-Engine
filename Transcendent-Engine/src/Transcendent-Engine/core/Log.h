#pragma once

#include "Transcendent-Engine/core/core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace TE {
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define TE_CORE_TRACE(...)    ::TE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TE_CORE_INFO(...)     ::TE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TE_CORE_WARN(...)     ::TE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TE_CORE_ERROR(...)    ::TE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TE_CORE_CRITICAL(...) ::TE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define TE_TRACE(...)         ::TE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TE_INFO(...)          ::TE::Log::GetClientLogger()->info(__VA_ARGS__)
#define TE_WARN(...)          ::TE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TE_ERROR(...)         ::TE::Log::GetClientLogger()->error(__VA_ARGS__)
#define TE_CRITICAL(...)      ::TE::Log::GetClientLogger()->critical(__VA_ARGS__)