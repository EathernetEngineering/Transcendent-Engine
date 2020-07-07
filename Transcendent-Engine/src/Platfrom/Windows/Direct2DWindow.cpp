#include <tepch.h>
#include <Platfrom/Windows/Direct2DWindow.h>

#include <Transcendent-Engine/Events/ApplicationEvent.h>

namespace TE {

	Direct2DWindow::Direct2DWindow() {
		Init(WindowProps());
	}

	Direct2DWindow::Direct2DWindow(const WindowProps& Props) {
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
		TE_CORE_ERROR("{0}; Error: {0}", msg, Error);
	}

	HRESULT Direct2DWindow::Init(const WindowProps& Props) {
		HRESULT hr = S_OK;

		hr = CreateDeviceResources();

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

			m_pWindow = CreateWindow(L"Direct2DWindow", L"Transcenednt Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
										static_cast<UINT>(ceil(1280.f * dpi / 96.f)), static_cast<UINT>(ceil(720.f * dpi / 96.f)), NULL, NULL,
										HINST_THISCOMPONANT, this);

			hr = m_pWindow ? S_OK : E_FAIL;
			if (SUCCEEDED(hr)) {
				ShowWindow(m_pWindow, SW_SHOWNORMAL);
				UpdateWindow(m_pWindow);
			} else {
				HandleError("Could not create window");
			}
		} else {
			HandleError("Could not create device-dependent resources");
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

	template<class T>
	inline void Direct2DWindow::SafeRelease(T** InterfaceToRelease) noexcept {
		if (*InterfaceToRelease == NULL)
			;
		else {
			(*InterfaceToRelease)->Release();
			(*InterfaceToRelease) = NULL;
		}
	}
}
