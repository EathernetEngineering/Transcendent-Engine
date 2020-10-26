#pragma once

#include "Transcendent-Engine/core/Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TE {

	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(const WindowProps& props);
		virtual ~OpenGLWindow();

		void OnUpdate() override;

		inline uint32_t GetWidth(void) const override { return m_Data.Width; }
		inline uint32_t GetHeight(void) const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync(void) const override;

		inline virtual void* GetNativeWindow(void) const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
