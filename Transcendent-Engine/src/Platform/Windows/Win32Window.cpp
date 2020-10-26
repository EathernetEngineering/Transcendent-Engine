#include <tepch.h>
#include <Platform/Windows/Win32Window.h>

#include <Transcendent-Engine/Events/ApplicationEvent.h>
#include <Transcendent-Engine/Events/KeyEvent.h>
#include <Transcendent-Engine/Events/MouseEvent.h>

namespace TE {

	Win32Window::Win32Window(const WindowProps& Props)
		: m_Width(Props.Width), m_Height(Props.Height), m_Window(nullptr), m_VSync(Props.VSync),
			m_Title(std::wstring(Props.Title.begin(), Props.Title.end())), m_EventCallback(nullptr)
	{
		CreateWin32Window();
	}

	void Win32Window::CreateWin32Window()
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hbrBackground = 0;
		wc.lpfnWndProc = wndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(NULL);
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = L"Win32Window";
		wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
		
		bool res = RegisterClassEx(&wc);
		TE_CORE_ASSERT(res, "Failed to register class");

		RECT wr = { 0, 0, static_cast<LONG>(m_Width), static_cast<LONG>(m_Height) };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

		TE_CORE_INFO("Creating Win32 Window: {0}: Width: {1}, Height: {2}", std::string(m_Title.begin(), m_Title.end()).c_str(), wr.right - wr.left, wr.bottom - wr.top);

		m_Window = CreateWindowEx(0, L"Win32Window", m_Title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, GetModuleHandle(NULL), this);
		char ErrorMessage[64];
		sprintf_s(ErrorMessage, "Failed to crete window; Win32Error: %#X", GetLastError());
		TE_CORE_ASSERT(m_Window != nullptr, ErrorMessage);

		ShowWindow(m_Window, SW_SHOWDEFAULT);
	}

	void Win32Window::OnUpdate(void)
	{
		MSG msg = { 0 };
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				{
					WindowCloseEvent event;
					this->m_EventCallback(event);
				}
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	void Win32Window::Resize(UINT Width, UINT Height)
	{
		return;
	}

	LRESULT Win32Window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_CREATE) {
			/*
			 * Save pointer to window passed into the createWinodw function
			 */
			LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
			return 1;
		} 
		else 
		{
			Win32Window* window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			switch (message) {
			case WM_KEYDOWN:
				{
					KeyPressedEvent event(static_cast<KeyCode>(wParam), 0);
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_KEYUP:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(wParam));
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_MOUSEHWHEEL:
				{
					MouseScrolledEvent event(HIWORD(wParam), 0);
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_MOUSEMOVE:
				{
					MouseMovedEvent event(LOWORD(lParam), HIWORD(lParam));
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_LBUTTONDOWN:
				{
					MouseButtonPressedEvent event(TE_MOUSE_BUTTON_0);
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_RBUTTONDOWN:
				{
					MouseButtonPressedEvent event(TE_MOUSE_BUTTON_1);
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_MBUTTONDOWN:
				{
					MouseButtonPressedEvent event(TE_MOUSE_BUTTON_2);
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_LBUTTONUP:
				{
					MouseButtonReleasedEvent event(TE_MOUSE_BUTTON_0);
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_RBUTTONUP:
				{
					MouseButtonReleasedEvent event(TE_MOUSE_BUTTON_1);
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_MBUTTONUP:
				{
					MouseButtonReleasedEvent event(TE_MOUSE_BUTTON_2);
					if (window->m_EventCallback) window->m_EventCallback(event);
				}
				return 0;

			case WM_SIZE:
				{
					WindowResizeEvent event(LOWORD(lParam), HIWORD(lParam));
					if (window->m_EventCallback) window->m_EventCallback(event);
					window->Resize(LOWORD(lParam), HIWORD(lParam));
				}
				return DefWindowProc(hWnd, message, wParam, lParam); // TODO: IMPLEMENT MY OWN RESIZE FUNCTION

			case WM_DESTROY:
				PostQuitMessage(0);
				return 1;

			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
	}

}
