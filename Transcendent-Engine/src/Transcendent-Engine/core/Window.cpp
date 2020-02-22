#include "tepch.h"
#include "Transcendent-Engine/core/Window.h"
#include "Platfrom/OpenGL/OpenGLWindow.h"

namespace TE {

	Scope<Window> Window::Create(const WindowProps& props) {

		#ifdef TE_PLATFORM_WINDOWS
			return CreateScope<OpenGLWindow>(props);
		#else
			TE_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}
