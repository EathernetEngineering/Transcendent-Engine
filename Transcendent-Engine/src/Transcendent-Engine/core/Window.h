#pragma once

#include "tepch.h"

#include "Transcendent-Engine/core/core.h"
#include "Transcendent-Engine/Events/Event.h"

namespace TE {

	struct WindowProps
	{
		std::string Title;
		unsigned int width;
		unsigned int height;

		WindowProps(std::string Title = "Transcendent Engine",
						unsigned int width = 1280u,
						unsigned int height = 720u)
		{
		}
	};

	// Interface representing a desktop based window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate();

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallbackFn(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}
