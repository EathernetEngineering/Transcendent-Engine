#include <tepch.h>

#include <Platform/Windows/Direct2DWindow.h>

#include <Transcendent-Engine/Events/ApplicationEvent.h>

namespace TE {

	Direct2DWindow::Direct2DWindow(const WindowProps& Props)
		: m_Data({ Props.Title, Props.Width, Props.Height, false, nullptr, nullptr })
	{
		Init(Props);
	}

	Direct2DWindow::~Direct2DWindow() {
		Shutdown();
	}

	void Direct2DWindow::HandleError() {
		DWORD Error = GetLastError();
		TE_CORE_ERROR("Unknown error: {0}", Error);
	}

	void Direct2DWindow::HandleError(const std::string& msg) {
		DWORD Error = GetLastError();
		TE_CORE_ERROR("{0}; Error: {1}", msg, Error);
	}

	HRESULT Direct2DWindow::Init(const WindowProps& Props) {
		HRESULT hr = S_OK;

		hr = CreateDeviceIndependantResources();

		if (SUCCEEDED(hr)) {
			WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = sizeof(LONG_PTR);
			wcex.hInstance = HINST_THISCOMPONANT;
			wcex.hbrBackground = NULL;
			wcex.lpszMenuName = NULL;
			wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
			wcex.lpszClassName = L"Direct2DWindow";
				
			RegisterClassEx(&wcex);

			UINT dpi = GetDpiForSystem();

			std::wstring Title = std::wstring(Props.Title.begin(), Props.Title.end());
			m_pWindow = CreateWindow(L"Direct2DWindow", Title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
										static_cast<UINT>(ceil((float)Props.Width * dpi / 96.f)), static_cast<UINT>(ceil((float)Props.Height * dpi / 96.f)),
										NULL, NULL, HINST_THISCOMPONANT, this);

			hr = m_pWindow ? S_OK : E_FAIL;
			if (SUCCEEDED(hr)) {
				ShowWindow(m_pWindow, SW_SHOWNORMAL);
				UpdateWindow(m_pWindow);
			} else {
				HandleError("Could not create window");
			}
		} else {
			HandleError("Could not create device-independent resources");
		}

		return hr;
	}

	void Direct2DWindow::Shutdown() {
		DiscardDeviceResources();
	}

	void Direct2DWindow::DiscardDeviceResources() {
		try {
			Release(&m_Data.pDirect2dFactory);
			Release(&m_Data.pRenderTarget);
		} catch (NullReferenceException& e) {
			TE_CORE_ERROR("{0}", e.what());
		}
	}

	void Direct2DWindow::OnUpdate() {
		RunMessageLoop();
	}

	void Direct2DWindow::RunMessageLoop() {
		MSG msg;
		BOOL bRet = 0;

		if ((bRet = GetMessage(&msg, NULL, 0u, 0u)) != 0) {
			if (bRet == -1) {
				HandleError();
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			WindowCloseEvent event;
			m_Data.EventCallback(event);
		}
	}

	template<class Interface>
	inline void Direct2DWindow::Release(Interface** InterfaceToRelease) {
		if (*InterfaceToRelease == NULL)
			throw NullReferenceException();
		else {
			(*InterfaceToRelease)->Release();
			(*InterfaceToRelease) = NULL;
		}
	}

	template<class Interface>
	inline void Direct2DWindow::SafeRelease(Interface** InterfaceToRelease) noexcept {
		if (*InterfaceToRelease == NULL)
			;
		else {
			(*InterfaceToRelease)->Release();
			(*InterfaceToRelease) = NULL;
		}
	}

	LRESULT CALLBACK Direct2DWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		LRESULT result = 0;

		if (message == WM_CREATE) {
			LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
			Direct2DWindow* pDirect2DWindow = (Direct2DWindow*)pcs->lpCreateParams;

			if (!(::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pDirect2DWindow))))
				if(GetLastError())
					HandleError("Filed to set window pointer");

		} else {
			Direct2DWindow* pDirect2DWindow = reinterpret_cast<Direct2DWindow*>(static_cast<LONG_PTR>(::GetWindowLongPtr(hwnd, GWLP_USERDATA)));

			bool wasHandled = false;

			if (pDirect2DWindow) {
				switch (message) {
				case WM_SIZE:
					{
						UINT Width = LOWORD(lParam);
						UINT Height = HIWORD(lParam);
						pDirect2DWindow->OnWindowResize(Width, Height);
						if(pDirect2DWindow->OnResizeEvent)
							pDirect2DWindow->OnResizeEvent();
					}
					result = 0;
					wasHandled = true;
					break;

				case WM_DISPLAYCHANGE:
					{
						InvalidateRect(hwnd, NULL, FALSE);
					}
					result = 0;
					wasHandled = true;
					break;

				case WM_PAINT:
					{
						pDirect2DWindow->OnRender();
						ValidateRect(hwnd, NULL);
					}
					result = 0;
					wasHandled = true;
					break;

				case WM_DESTROY:
					{
						PostQuitMessage(0);
						if (pDirect2DWindow->OnQuitEvent)
							pDirect2DWindow->OnQuitEvent();
					}
					result = 1;
					wasHandled = true;
					break;

				}
			} else if (GetLastError()) {
				HandleError("pDirect2DWindow was NULL");
			}
			if (!wasHandled) {
				result = DefWindowProc(hwnd, message, wParam, lParam);
			}
		}

		return result;
	}

	void Direct2DWindow::OnWindowResize(UINT Width, UINT Height) {
		if (m_Data.pRenderTarget) {
			m_Data.pRenderTarget->Resize(D2D1::SizeU(Width, Height));
		}
	}

	HRESULT Direct2DWindow::CreateDeviceResources() {
		HRESULT hr = S_OK;

		if (!m_Data.pRenderTarget) {
			RECT rc;
			GetClientRect(m_pWindow, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

			hr = m_Data.pDirect2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_pWindow, size),
																	&m_Data.pRenderTarget);
		}

		return hr;
	}
	
	HRESULT Direct2DWindow::CreateDeviceIndependantResources() {
		HRESULT hr = S_OK;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Data.pDirect2dFactory);

		return hr;
	}

	void Direct2DWindow::OnRender() {
		if (!(SUCCEEDED(CreateDeviceResources())))
			HandleError("Failed to create device-dependant resources");
	}
}
