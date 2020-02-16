#pragma once

#include <memory>

#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		#define TE_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
#	endif
#elif defined(__APPLE__) || (__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure we're that running on MAC
	 * and npot some other apple platform 
	 */
		 
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define TE_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC ==1
		#define TE_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based off the linux kerna;
 * it has __linux__ defined 
 */
#elif defined(__ANDROID__)
	#define TE_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define TE_PLATFORM_LINUX
	#error "Linux is not supported!"
#else 
	/* Unknown compiler or platform */
	#error "Unknown platform!"
#endif

#ifdef TE_ENABLE_ASSERTS
	#define TE_ASSERT(x, ...) { if(!(x)) { TE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TE_CORE_ASSERT(x, ...) { if(!(x)) { TE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TE_ASSERT(x, ...)
	#define TE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace TE  {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward < Args(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
