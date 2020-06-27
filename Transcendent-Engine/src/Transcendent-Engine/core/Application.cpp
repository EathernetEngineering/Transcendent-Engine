#include "tepch.h"

#include "Transcendent-Engine/core/Application.h"
#include "Transcendent-Engine/core/Log.h"

#include "Transcendent-Engine/Renderer/Renderer.h"
#include "Transcendent-Engine/Renderer/Renderer2D.h"
#include "Transcendent-Engine/Renderer/ShaderLibrary.h"

#include "glm/gtc/type_ptr.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

uint32_t MemoryData::Allocations = 0;
uint32_t MemoryData::Deletions   = 0;
uint32_t MemoryData::memalloc    = 0;
uint32_t MemoryData::memfree     = 0;
uint32_t MemoryData::AllocationsAtTime() 
{ 
	return Allocations - Deletions; 
}
uint32_t MemoryData::memattime() 
{ 
	return memalloc - memfree; 
}
std::shared_ptr<std::string> MemoryData::memattimeString() 
{ 
	uint64_t temp = memalloc - memfree;
	if (temp <= 1024)
		return std::make_shared<std::string>(std::to_string(memalloc - memfree) + "B");
	else if (temp > 1024 && temp <= 1024 * 1024)
		return std::make_shared<std::string>(std::to_string((memalloc - memfree) / 1024) + "kB");
	else if (temp > 1024 * 1024 && temp <= 1024 * 1024 * 1024)
		return std::make_shared<std::string>(std::to_string((memalloc - memfree) / 1024 * 1024) + "MB");
	else if (temp > 1024 * 1024 * 1024)
		return std::make_shared<std::string>(std::to_string((memalloc - memfree) / 1024 * 1024 * 1024) + "GB");
	else
		return std::make_shared<std::string>("ERROR");
}
std::shared_ptr<std::string> MemoryData::TotalMemoryString() 
{ 
	uint64_t temp = memalloc;
	if (temp <= 1024)
		return std::make_shared<std::string>(std::to_string(memalloc) + "B");
	else if (temp > 1024 && temp <= 1024 * 1024)
		return std::make_shared<std::string>(std::to_string((memalloc) / 1024) + "kB");
	else if (temp > 1024 * 1024 && temp <= 1024 * 1024 * 1024)
		return std::make_shared<std::string>(std::to_string((memalloc) / 1024 * 1024) + "MB");
	else if (temp > 1024 * 1024 * 1024)
		return std::make_shared<std::string>(std::to_string((memalloc) / 1024 * 1024 * 1024) + "GB");
	else
		return std::make_shared<std::string>("ERROR");
}

void* operator new(size_t size) {

	MemoryData::memalloc += size;
	MemoryData::Allocations++;

	return malloc(size);
}

void operator delete(void* memory, size_t size) {
	
	MemoryData::memfree += size;
	MemoryData::Deletions++;
	
	free(memory);
}

namespace TE {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		TE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(TE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		ShaderLibrary::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		#if defined TE_DEBUG
			m_DebugLayer = new DebugLayer("Debug");
			PushLayer(m_DebugLayer);
		#endif

		Renderer2D::Init();
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

		TE_CORE_WARN("Allocated {0} of heap memory with a total of {1} allocations.", MemoryData::TotalMemoryString()->c_str(), MemoryData::Allocations);

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

		glm::vec4 color(0.0f, 0.0f, 0.0f, 1.0f);
		bool clearColourWindowOpen;
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

				ImGui::Begin("Window Options");
				ImGui::ColorEdit3("Clear colour", glm::value_ptr(color));
				ImGui::End();

				m_ImGuiLayer->End();
			}
			glfwSwapBuffers((GLFWwindow*)m_Window->GetNativeWindow());
			m_Window->OnUpdate();
		}
	}
}
