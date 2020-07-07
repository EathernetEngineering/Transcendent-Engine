#pragma once

#include <Transcendent-Engine/core/Window.h>

#include <d2d1.h>

#ifndef HINST_THISCOMPONANT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONANT ((HINSTANCE)&__ImageBase)
#endif

namespace TE {

	class Direct2DWindow : public Window
	{
	public:
		Direct2DWindow(const WindowProps& Props);
		Direct2DWindow();
		virtual ~Direct2DWindow();

		virtual void OnUpdate() override;
		inline virtual uint32_t GetWidth()  const override { return m_Data.Width;  }
		inline virtual uint32_t GetHeight() const override { return m_Data.Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override { return m_Data.VSync; }

		inline virtual void* GetNativeWindow() const override { return m_pWindow; }

	private:
		virtual HRESULT Init(const WindowProps& Props);
		virtual void Shutdown();

		template<typename T>
		inline void Release(T** InterfaceToRelease);

		template<typename T>
		inline void SafeRelease(T** InterfaceToRelease) noexcept;

		void HandleError();
		void HandleError(const std::string& msg);

		virtual void RunMessageLoop();

		HRESULT CreateDeviceIndependentResources();
		HRESULT CreateDeviceResources();

		void DiscardDeviceResources();

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam);

	private:
		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			ID2D1Factory* pDirect2dFactory;
			ID2D1HwndRenderTarget* pRenderTarget;

			EventCallbackFn EventCallback;
		};

	private:
		HWND m_pWindow;
		WindowData m_Data;
	};

}
