#include "tepch.h"
#include "Transcendent-Engine/core/Input.h"

#ifdef TE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace TE {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef TE_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
	#else
		TE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
}