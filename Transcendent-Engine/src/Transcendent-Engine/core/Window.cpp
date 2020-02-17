#include "tepch.h"
#include "Transcendent-Engine/core/Window.h"

#ifdef TE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace TE {

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef TE_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			TE_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}
