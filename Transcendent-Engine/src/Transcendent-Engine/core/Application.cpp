#include "tepch.h"

#include "Transcendent-Engine/core/Application.h"
#include "Transcendent-Engine/core/Log.h"

#include "Transcendent-Engine/Renderer/Renderer.h"

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

		while (m_Running) 
		{
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
				m_ImGuiLayer->End();
			}
			glfwSwapBuffers((GLFWwindow*)m_Window->GetNativeWindow());
			m_Window->OnUpdate();
		}
	}
}
