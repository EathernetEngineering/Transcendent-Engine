#pragma once

#include <Transcendent-Engine/Core/Window.h>

namespace TE {

	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProps& Props);
		~Win32Window() = default;

		virtual void OnUpdate(void);

		inline virtual uint32_t GetWidth(void)  const override { return m_Width; }
		inline virtual uint32_t GetHeight(void) const override { return m_Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_EventCallback = callback; }
		virtual void SetVSync(bool VSync) override { m_VSync = VSync; }
		inline virtual bool IsVSync(void) const override { return m_VSync; }

		inline virtual void* GetNativeWindow(void) const override { return m_Window; }

	private:
		void CreateWin32Window();
		void Resize(UINT Width, UINT Height);

	protected:
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_Window;
		bool m_VSync;
		uint32_t m_Width, m_Height;
		std::wstring m_Title;

		EventCallbackFn m_EventCallback;
	};

}
