#pragma once

#include <Transcendent-Engine/core/Window.h>

#include <d2d1.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <Platform/Windows/d3dx12.h>

#include <wrl.h>

#ifndef HINST_THISCOMPONANT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONANT ((HINSTANCE)&__ImageBase)
#endif

namespace TE {

	class DirectX12Window : public Window
	{
	public:
		DirectX12Window(const WindowProps& Props);
		virtual ~DirectX12Window();

		virtual void OnUpdate() override;
		inline virtual uint32_t GetWidth()  const override { return m_WindowData.Width;  }
		inline virtual uint32_t GetHeight() const override { return m_WindowData.Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_WindowData.EventCallback = callback; }

		virtual void SetVSync(bool enabled) override {};
		virtual bool IsVSync() const override { return m_WindowData.VSync; }

		inline virtual void* GetNativeWindow() const override { return m_pWindow; }

	private:
		virtual HRESULT Init();
		virtual void Shutdown() {};

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

		void OnResize(UINT Width, UINT Height);
		void OnRender();

		void GetHardwareAdapter(IDXGIFactory4* Factory, IDXGIAdapter1** HardwareAdapter);

		void LoadPipeline();

		void FlushGpu();

		void WaitForGpu() noexcept;

	private:
		struct WindowData
		{
			std::wstring Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		static struct PipelineData
		{
			static const UINT BufferSize = 2;

			D3D12_VIEWPORT                                 Viewport;
			D3D12_RECT                                     ScissorRect;
			Microsoft::WRL::ComPtr<IDXGISwapChain3>        SwapChain;
			Microsoft::WRL::ComPtr<ID3D12Device>           Device;
			Microsoft::WRL::ComPtr<ID3D12Resource>         RenderTargets[BufferSize];
			Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CommandAllocator;
			Microsoft::WRL::ComPtr<ID3D12CommandQueue>     CommandQueue;
			Microsoft::WRL::ComPtr<ID3D12RootSignature>    RootSignature;
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>   RtvHeap;
			Microsoft::WRL::ComPtr<ID3D12PipelineState>    PipelineState;
			Microsoft::WRL::ComPtr<ID3D12CommandList>      CommandList;
			UINT                                           rtvDescriptorSize;

			UINT                                           FrameIndex;
			HANDLE                                         FenceEvent;
			Microsoft::WRL::ComPtr<ID3D12Fence>            Fence;
			UINT64                                         FenceValue;
		};

	private:
		HWND m_pWindow;
		WindowData m_WindowData;

	public:
		PipelineData m_PipelineData;
	};

}
