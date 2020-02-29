#pragma once
#include "Transcendent-Engine/core/core.h"
#include "Transcendent-Engine/Events/Event.h"

namespace TE {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(std::string Title = "Transcendent Engine",
						unsigned int Width = 1280u,
						unsigned int Height = 720u)
			: Title(Title), Width(Width), Height(Height)
		{
		}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth(void) const = 0;
		virtual unsigned int GetHeight(void) const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enableed) = 0;
		virtual bool IsVSync(void) const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}
