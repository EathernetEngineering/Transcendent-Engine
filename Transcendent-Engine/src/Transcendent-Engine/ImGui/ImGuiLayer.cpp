#include "tepch.h"
#include "Transcendent-Engine/ImGui/ImGuiLayer.h"

#include "Transcendent-Engine/core/Application.h"

#include <Platform/Windows/DirectX12Window.h>

#include <ImGui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_dx12.h>
#include <examples/imgui_impl_win32.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TE {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach() {

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();

		// Setup Platform/Renderer bindings
#ifdef TE_PLATFORM_WINDOWS
		DirectX12Window* window = static_cast<DirectX12Window*>(&app.GetWindow());
		ImGui_ImplWin32_Init(window->GetNativeWindow());
		ImGui_ImplDX12_Init(window->m_PipelineData.Device.Get(), 2u, DXGI_FORMAT_R8G8B8A8_UNORM, window->m_PipelineData.RtvHeap->GetCPUDescriptorHandleForHeapStart(), window->m_PipelineData.RtvHeap->GetGPUDescriptorHandleForHeapStart());
#else
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
#endif
	}

	void ImGuiLayer::OnDetach() {
#ifdef TE_PLATFORM_WINDOWS
		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
#else
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
#endif

		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin() {

#ifdef TE_PLATFORM_WINDOWS
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
#else
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
#endif
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	}

	void ImGuiLayer::OnImGuiRender() { ; }

	void ImGuiLayer::End() {

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
#ifdef TE_PLATFORM_WINDOWS
		DirectX12Window* window = static_cast<DirectX12Window*>(&app.GetWindow());

		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = window->m_PipelineData.RenderTargets[window->m_PipelineData.FrameIndex].Get();
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		ID3D12GraphicsCommandList* g_pd3dCommandList = { 0 };
		D3D12_CPU_DESCRIPTOR_HANDLE g_mainRenderTargetDescriptor[2u] = { {0}, {0} };

		float ClearColour[4]{ 0.2f, 0.0f, 0.8f, 1.0f };

		g_pd3dCommandList->Reset(window->m_PipelineData.CommandAllocator.Get(), NULL);
		g_pd3dCommandList->ResourceBarrier(1, &barrier);
		g_pd3dCommandList->ClearRenderTargetView(g_mainRenderTargetDescriptor[window->m_PipelineData.FrameIndex], (float*)&ClearColour, 0, NULL);
		g_pd3dCommandList->OMSetRenderTargets(1, &g_mainRenderTargetDescriptor[window->m_PipelineData.FrameIndex], FALSE, NULL);
		g_pd3dCommandList->SetDescriptorHeaps(1, &window->m_PipelineData.RtvHeap);

		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_pd3dCommandList);

		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		g_pd3dCommandList->ResourceBarrier(1, &barrier);
		g_pd3dCommandList->Close();

		window->m_PipelineData.CommandQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&g_pd3dCommandList);

#else	
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}
