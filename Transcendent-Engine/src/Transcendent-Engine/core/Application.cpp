#include "tepch.h"
#include "Application.h"

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
}
