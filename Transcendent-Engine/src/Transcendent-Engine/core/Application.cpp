#include "tepch.h"

#include "Transcendent-Engine/core/Application.h"
#include "Transcendent-Engine/core/Log.h"

#include "Transcendent-Engine/Renderer/Renderer.h"

#include "imgui.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TE {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		TE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(TE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	 void Application::PushLayer(Layer* layer) {

		 m_LayerStack.PushLayer(layer);
		 layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(TE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(TE_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		m_Minimized = false;
		return true;

	}

	void Application::Run() {

		float colora[4] { 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 color(0.0f, 0.0f, 0.0f, 1.0f);
		while (m_Running) 
		{
			RenderCommand::SetClearColor(color);
			RenderCommand::Clear();
			if (!m_Minimized) {

				{
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();
				}

				m_ImGuiLayer->Begin();
				{
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				ImGuiWindowFlags flags = 0;
				flags |= ImGuiWindowFlags_NoCollapse;
				flags |= ImGuiWindowFlags_NoTitleBar;
				ImGui::Begin("Transcendent Engine", (bool*)1, flags);
				ImGui::Checkbox("Show Window Options:", &m_clearColourWindowOpen);
				ImGui::Checkbox("Show Demo Window:", &m_ShowDemoWindow);
				ImGui::Checkbox("Show About Window:", &m_ShowAboutWindow);
				ImGui::End();
				m_ImGuiLayer->SetShowDemoWindow(m_ShowDemoWindow);
				m_ImGuiLayer->SetShowAboutWindow(m_ShowAboutWindow);
				if (m_clearColourWindowOpen) {
					ImGui::Begin("Window Options", &m_clearColourWindowOpen, 0);
					ImGui::ColorEdit4("Clear colour", colora);
					color.r = colora[0];
					color.g = colora[1];
					color.b = colora[2];
					color.a = colora[3];

					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					ImGui::End();
				}
				m_ImGuiLayer->End();
			}
			glfwSwapBuffers((GLFWwindow*)m_Window->GetNativeWindow());
			m_Window->OnUpdate();
		}
	}
}
