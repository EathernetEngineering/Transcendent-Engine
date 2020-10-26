#pragma once
#include "Transcendent-Engine/core/core.h"
#include "Transcendent-Engine/Events/Event.h"

namespace TE {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;
		bool VSync;

		WindowProps(std::string Title = "Transcendent Engine",
						uint32_t Width = 1280u,
						uint32_t Height = 720u,
						bool VSync = true)
			: Title(Title), Width(Width), Height(Height), VSync(VSync)
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

		virtual uint32_t GetWidth(void) const = 0;
		virtual uint32_t GetHeight(void) const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enableed) = 0;
		virtual bool IsVSync(void) const = 0;

		inline virtual void* GetNativeWindow(void) const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}
