#include "tepch.h"
#include "Transcendent-Engine/core/Window.h"
#include "Platform/OpenGL/OpenGLWindow.h"
#include "Platform/Windows/DirectX12Window.h"

namespace TE {

	Scope<Window> Window::Create(const WindowProps& props) {

		#ifdef TE_PLATFORM_WINDOWS
			return CreateScope<DirectX12Window>(props);
		#else
			TE_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}
