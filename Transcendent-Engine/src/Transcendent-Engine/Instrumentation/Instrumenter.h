#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

#include <Transcendent-Engine/core/Log.h>

namespace TE {

	using DoubleMicroSeconds = std::chrono::duration<double, std::micro>;
	using DoubleMilliSeconds = std::chrono::duration<double, std::milli>;
	using FloatingPointMicroSeconds = std::chrono::duration<double, std::micro>;
	using FloatingPointMilliSeconds = std::chrono::duration<double, std::milli>;

	struct ProfileResult
	{
		std::string Name;

		DoubleMicroSeconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		void BeginSession(const std::string& Name, const std::string& Filepath = "results.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.

				if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
				{
					TE_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", Name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(Filepath);

			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new InstrumentationSession({ Name });
				WriteHeader();
			}
			else
			{
				if (Log::GetCoreLogger())
				{
					TE_CORE_ERROR("Instrumentor could not open results file '{0}'.", Filepath);
				}
			}
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& Result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (Result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << Result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << Result.ThreadID << ",";
			json << "\"ts\":" << Result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor Instance;
			return Instance;
		}

	private:
		Instrumentor()
			: m_CurrentSession(nullptr)
		{
		}

		~Instrumentor()
		{
			EndSession();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\":{}, \"traceEvents\":[{}";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		void InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}

	private:
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

	class IntrumentationTimer
	{
	public:
		IntrumentationTimer(const char* Name)
			: m_Name(Name), m_Stopped(false)
		{
		}
		
		~IntrumentationTimer()
		{
			if (m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimePoint = std::chrono::steady_clock::now();
			auto highResStart = DoubleMicroSeconds{ m_StartTimePoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
		bool m_Stopped;
	};

	namespace InstrumentorUtils
	{
		template<size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template<size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_T srcIndex = 0;
			size_t stdIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	};

}

#define TE_PROFILE 0
#ifndef TE_PROFILE
#define TE_PROFILE 0
#endif
#if TE_PROFILE

	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define TE_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define TE_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define TE_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define TE_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define TE_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define TE_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define TE_FUNC_SIG __func__
	#else
		#define TE_FUNC_SIG "TE_FUNC_SIG unknown!"
	#endif
	
	#define TE_PROFILE_BEGIN_SESSION(name, filepath) ::TE::Instrumentor::Get().BeginSession(name, filepath)
	#define TE_PROFILE_END_SESSION() ::TE::Instrumentor::Get().EndSession()
	#define TE_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::TE::InstrumentorUtils::CleanupOutputString(name, "__cdecl"); ::TE::IntrumentationTimer timer##line(fixedName##line.Data)
	
	#define TE_PROFILE_SCOPE_LINE(name, line) TE_PROFILE_SCOPE_LINE2(name, line)
	#define TE_PROFILE_SCOPE(name) TE_PROFILE_SCOPE_LINE(name, __LINE__)
	#define TE_PROFILE_FUNCTION() TE_PROFILE_SCOPE(TE_FUNC_SIG)
#else
	#define TE_PROFILE_BEGIN_SESSION(name, filepath)
	#define TE_PROFILE_END_SESSION()
	#define TE_PROFILE_SCOPE(name)
	#define TE_PROFILE_FUNCTION()
#endif
