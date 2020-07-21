#include <tepch.h>

#include <Platform/Windows/DirectX12Window.h>

#include <Transcendent-Engine/core/Input.h>
#include <Transcendent-Engine/Events/ApplicationEvent.h>
#include <Transcendent-Engine/Events/KeyEvent.h>
#include <Transcendent-Engine/Events/MouseEvent.h>

namespace TE {

	DirectX12Window::DirectX12Window(const WindowProps& Props)
		: m_WindowData({ std::wstring(Props.Title.begin(), Props.Title.end()), Props.Width, Props.Height, false, Props.Callback })
	{
		if (!(SUCCEEDED(Init())))
			HandleError("Could not initalize window class");
	}

	DirectX12Window::~DirectX12Window() {
		Shutdown();
	}

	HRESULT DirectX12Window::Init() {
		HRESULT hr;

		WNDCLASSEX wcex = { 0 };
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.hInstance = HINST_THISCOMPONANT;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = L"DirectX12Window";
		RegisterClassEx(&wcex);

		RECT WndRect = { 0, 0, static_cast<LONG>(m_WindowData.Width), static_cast<LONG>(m_WindowData.Height) };
		AdjustWindowRect(&WndRect, WS_OVERLAPPEDWINDOW, FALSE);


		TE_CORE_INFO("Creating Window: {0} ({1}, {2})", std::string(m_WindowData.Title.begin(), m_WindowData.Title.end()), m_WindowData.Width, m_WindowData.Height);

		m_pWindow = CreateWindow(wcex.lpszClassName, m_WindowData.Title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
									CW_USEDEFAULT, m_WindowData.Width, m_WindowData.Height,
									nullptr, nullptr, HINST_THISCOMPONANT, this);

		hr = m_pWindow ? S_OK : E_FAIL;

		LoadPipeline();

		if (SUCCEEDED(hr)) {
			ShowWindow(m_pWindow, SW_SHOWNORMAL);
			UpdateWindow(m_pWindow);
		}

		return hr;

	}

	void DirectX12Window::OnUpdate() {
		MSG msg = {};
		if (msg.message != WM_QUIT)
		{
			// Process any messages in the queue.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			WindowCloseEvent event;
			m_WindowData.EventCallback(event);
		}
	}

	LRESULT CALLBACK DirectX12Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		LRESULT rs = 0;

		DirectX12Window* pSample = reinterpret_cast<DirectX12Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		bool WasHandled = false;

		switch(message) {
		case WM_CREATE:
			{
				LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
				SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
			}
			rs = 1;
			return rs;

		case WM_KEYDOWN:
			if (pSample) {
				KeyPressedEvent event(static_cast<KeyCode>(wParam), 0);
				pSample->m_WindowData.EventCallback(event);
			}
			WasHandled = true;
			rs = 0;
			break;

		case WM_KEYUP:
			if (pSample) {
				KeyReleasedEvent event(static_cast<KeyCode>(wParam));
				pSample->m_WindowData.EventCallback(event);
			}
			WasHandled = true;
			rs = 0;
			break;

		case WM_SIZE:
			if (pSample) {
				UINT Width = LOWORD(lParam);
				UINT Height = HIWORD(lParam);
				pSample->OnResize(Width, Height);

				WindowResizeEvent event(Width, Height);
				pSample->m_WindowData.EventCallback(event);
			}
			rs = 0;
			WasHandled = true;
			break;

		case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			rs = 0;
			WasHandled = true;
			break;

		case WM_PAINT:
			if (pSample) {
				pSample->OnRender();
				ValidateRect(hwnd, NULL);
			}
			WasHandled = true;
			rs = 0;
			break;

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				WindowCloseEvent event;
				pSample->m_WindowData.EventCallback(event);
			}
			WasHandled = true;
			rs = 1;
			break;
		}
		if (!WasHandled)
			rs = DefWindowProc(hwnd, message, wParam, lParam);

		return rs;
	}

	void DirectX12Window::OnResize(UINT Width, UINT Height) {
		HRESULT rs = S_OK;
		WaitForGpu();

		if (m_PipelineData.CommandQueue && m_PipelineData.Fence && m_PipelineData.FenceEvent)
		{
			rs = m_PipelineData.CommandAllocator->Reset();
			if (FAILED(rs)) {
				HandleError("Failed to reset command allocator");
				return;
			}
			rs = m_PipelineData.CommandList->Release();
			if (FAILED(rs)) {
				HandleError("Failed to release command list");
				return;
			}
			for (UINT i = 0u; i < m_PipelineData.BufferSize; i++) {
				rs = m_PipelineData.RenderTargets[i]->Release();
				if (FAILED(rs)) {
					HandleError("Failed to release render target " + i);
					return;
				}
			}

			m_PipelineData.FrameIndex = 0u;

			rs = m_PipelineData.SwapChain->ResizeBuffers(m_PipelineData.BufferSize, Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0u);

			if (FAILED(rs)) {
				HandleError("Failed to resize buffers");
				return;
			}
		}
	}

	void DirectX12Window::OnRender() {

	}

	void DirectX12Window::LoadPipeline() {

		using namespace Microsoft::WRL;

		UINT FactoryFlags = 0;
		HRESULT rs = S_OK;

#ifdef TE_DEBUG
		{
			TE_PROFILE_SCOPE("DirectX12Window EnableDebugLayer");

			ComPtr<ID3D12Debug> DebugController;
			rs = D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController));
			if (SUCCEEDED(rs)) {
				DebugController->EnableDebugLayer();

				FactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
			} else {
				HandleError("Could not get debug interface");
			}
		}
#endif

		ComPtr<IDXGIFactory4> Factory;
		{
			TE_PROFILE_SCOPE("DirectX12Window CreateFactory");

			rs = CreateDXGIFactory2(FactoryFlags, IID_PPV_ARGS(&Factory));
			if (!SUCCEEDED(rs)) {
				throw std::runtime_error("Failed to create factory");
			}
		}

		{
			TE_PROFILE_SCOPE("DirectX12Window CreateSwapDevice");

			ComPtr<IDXGIAdapter1> HardwareAdapter;
			GetHardwareAdapter(Factory.Get(), &HardwareAdapter);

			rs = D3D12CreateDevice(HardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_PipelineData.Device));
			if (!SUCCEEDED(rs)) {
				HandleError("Failed to create device");
			}
		}

		{
			TE_PROFILE_SCOPE("DirectX12Window CreateCommandQueue");

			D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
			QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

			rs = m_PipelineData.Device->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&m_PipelineData.CommandQueue));
			if (!SUCCEEDED(rs)) {
				HandleError("Failed to create command queue");
			}
		}

		ComPtr<IDXGISwapChain1> SwapChain;
		{
			TE_PROFILE_SCOPE("DirectX12Window CreateSwapChain");

			DXGI_SWAP_CHAIN_DESC1 SwapChainDesc = {};
			SwapChainDesc.BufferCount = m_PipelineData.BufferSize;
			SwapChainDesc.Width = m_WindowData.Width;
			SwapChainDesc.Height = m_WindowData.Height;
			SwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			SwapChainDesc.SampleDesc.Count = 1;

			rs = Factory->CreateSwapChainForHwnd(m_PipelineData.CommandQueue.Get(), this->m_pWindow, &SwapChainDesc, nullptr, nullptr, &SwapChain);
			if (!SUCCEEDED(rs)) {
				HandleError("Failed to create swap chain");
			}
		}

		rs = Factory->MakeWindowAssociation(this->m_pWindow, DXGI_MWA_NO_ALT_ENTER);
		if (!SUCCEEDED(rs)) {
			HandleError("Failed to create window association");
		}

		rs = SwapChain.As(&m_PipelineData.SwapChain);
		m_PipelineData.FrameIndex = m_PipelineData.SwapChain->GetCurrentBackBufferIndex();
		if (!SUCCEEDED(rs)) {
			HandleError("Failed to set swap chain");
		}

		{
			TE_PROFILE_SCOPE("DirectX12Window CreateDescriptorHeaps");

			D3D12_DESCRIPTOR_HEAP_DESC RtvHeapDesc = {};
			RtvHeapDesc.NumDescriptors = m_PipelineData.BufferSize;
			RtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			RtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			rs = m_PipelineData.Device->CreateDescriptorHeap(&RtvHeapDesc, IID_PPV_ARGS(&m_PipelineData.RtvHeap));
			m_PipelineData.rtvDescriptorSize = m_PipelineData.Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

			if (!SUCCEEDED(rs)) {
				HandleError("Failed to create descriptor heap");
			}
		}

		{
			TE_PROFILE_SCOPE("DirectX12Window CreateFrameResources");

			CD3DX12_CPU_DESCRIPTOR_HANDLE RtvHandle(m_PipelineData.RtvHeap->GetCPUDescriptorHandleForHeapStart());

			for (UINT n = 0; n < m_PipelineData.BufferSize; n++) {
				rs = m_PipelineData.SwapChain->GetBuffer(n, IID_PPV_ARGS(&m_PipelineData.RenderTargets[n]));
				if (!SUCCEEDED(rs)) {
					HandleError("Failed to create render target" + n);
				}
				m_PipelineData.Device->CreateRenderTargetView(m_PipelineData.RenderTargets[n].Get(), nullptr, RtvHandle);
				RtvHandle.Offset(1, m_PipelineData.rtvDescriptorSize);
			}
		}

		rs = m_PipelineData.Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_PipelineData.CommandAllocator));
		if (!SUCCEEDED(rs)) {
			HandleError("Failed to create command allocator");
		}
	}

	void DirectX12Window::GetHardwareAdapter(IDXGIFactory4* Factory, IDXGIAdapter1** HardwareAdapter) {
		using namespace Microsoft::WRL;

		ComPtr<IDXGIAdapter1> Adapter;
		*HardwareAdapter = nullptr;
		
		for (UINT AdapterIndex = 0; DXGI_ERROR_NOT_FOUND != Factory->EnumAdapters1(AdapterIndex, &Adapter); ++AdapterIndex) {
			DXGI_ADAPTER_DESC1 Desc;
			Adapter->GetDesc1(&Desc);

			if (Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
				continue;
			}

			if (SUCCEEDED(D3D12CreateDevice(Adapter.Get(), D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr))) {
				break;
			}
		}

		*HardwareAdapter = Adapter.Detach();
	}

	void DirectX12Window::FlushGpu() {
		for (UINT i = 0; i < m_PipelineData.BufferSize; i++) {
			UINT64 fenceValue = ++m_PipelineData.FenceValue;
			m_PipelineData.CommandQueue->Signal(m_PipelineData.Fence.Get(), fenceValue);
			if (m_PipelineData.Fence->GetCompletedValue() < fenceValue) {
				m_PipelineData.Fence->SetEventOnCompletion(fenceValue, m_PipelineData.FenceEvent);
				WaitForSingleObject(m_PipelineData.FenceEvent, INFINITE);
			}
		}

		m_PipelineData.FrameIndex = 0;
	}

	void DirectX12Window::WaitForGpu() noexcept {
		if (m_PipelineData.CommandQueue && m_PipelineData.Fence && m_PipelineData.FenceEvent) {
			
			UINT64 fenceValue = m_PipelineData.FenceValue;

			if (SUCCEEDED(m_PipelineData.CommandQueue->Signal(m_PipelineData.Fence.Get(), fenceValue))) {
				if (SUCCEEDED(m_PipelineData.Fence->SetEventOnCompletion(fenceValue, m_PipelineData.FenceEvent))) {
					WaitForSingleObjectEx(m_PipelineData.FenceEvent, INFINITE, FALSE);

					m_PipelineData.FenceValue++;
				}
			}
		}
	}
}
