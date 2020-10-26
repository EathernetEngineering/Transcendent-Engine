#include "tepch.h"
#include "Transcendent-Engine/core/Window.h"
#include "Platform/OpenGL/OpenGLWindow.h"
#include "Platform/Windows/Win32Window.h"

namespace TE {

	Scope<Window> Window::Create(const WindowProps& props) {

		#ifdef TE_PLATFORM_WINDOWS
			return CreateScope<Win32Window>(props);
		#else
			TE_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}
