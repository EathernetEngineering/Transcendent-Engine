#include "tepch.h"
#include "Transcendent-Engine/core/Application.h"
#include "Transcendent-Engine/core/Log.h"

#include "Transcendent-Engine/core/Input.h"

#include <GLFW/glfw3.h>

namespace TE {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		TE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create();
	}

	void Application::Run() {

		while (!glfwWindowShouldClose((GLFWwindow*)m_Window->GetNativeWindow())) 
		{
			m_Window->OnUpdate();
		}
		m_Window->~Window();
		m_Window = nullptr;
		while (true);
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(TE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(TE_BIND_EVENT_FN(Application::OnWindowResize));
	}

	void Application::OnWindowClose() {

	}

	void Application::OnWindowResize() {

	}
}
