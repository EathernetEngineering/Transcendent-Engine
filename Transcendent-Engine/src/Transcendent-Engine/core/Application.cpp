#include "tepch.h"

#include "Transcendent-Engine/core/Application.h"
#include "Transcendent-Engine/core/Log.h"

#include "Transcendent-Engine/Renderer/Renderer.h"
#include "Transcendent-Engine/Renderer/Renderer2D.h"
#include "Transcendent-Engine/Renderer/ShaderLibrary.h"

#include "glm/gtc/type_ptr.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace MemoryAllocInfo {
	size_t memalloc = 0;
	size_t memfree = 0;
	size_t memattime() { return memalloc - memfree; }
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size) {

	MemoryAllocInfo::memalloc += size;

	return malloc(size);
}

void operator delete(void* memory, size_t size) {
	
	MemoryAllocInfo::memfree -= size;
	
	return free(memory);
}

namespace TE {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		TE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(TE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		//ShaderLibrary::Init();

		//m_ImGuiLayer = new ImGuiLayer();
		//PushOverlay(m_ImGuiLayer);

		#if defined _DEBUG
			//m_DebugLayer = new DebugLayer("Debug");
			//PushLayer(m_DebugLayer);
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
		if (MemoryAllocInfo::memalloc <= (1024u))
			TE_CORE_WARN("Allocated {0} B of memory on the heap during runtime.", MemoryAllocInfo::memalloc);
		else if (MemoryAllocInfo::memalloc <= (1024u * 1024u))
			TE_CORE_WARN("Allocated {0} KB of memory on the heap during runtime.", (float)(MemoryAllocInfo::memalloc) / (1024.0f));
		else if (MemoryAllocInfo::memalloc <= (1024u * 1024u * 1024u))
			TE_CORE_WARN("Allocated {0} MB of memory on the heap during runtime.", (float)(MemoryAllocInfo::memalloc) / (1024.0f * 1024.0f));
		else if (MemoryAllocInfo::memalloc > (1024u * 1024u * 1024u))
			TE_CORE_WARN("Allocated {0} GB of memory on the heap during runtime.", (float)(MemoryAllocInfo::memalloc) / (1024.0f * 1024.0f * 1024.0f));
		else
			TE_CORE_WARN("Allocated {0} B of memory on the heap during runtime.", MemoryAllocInfo::memalloc);

		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		//glViewport(0, 0, e.GetWidth(), e.GetHeight());

		m_Minimized = false;
		return true;

	}

	void Application::Run() {

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

				//m_ImGuiLayer->Begin();
				//{
				//	for (Layer* layer : m_LayerStack)
				//		layer->OnImGuiRender();
				//}
				//
				//ImGui::Begin("Window Options");
				//ImGui::ColorEdit3("Clear colour", glm::value_ptr(color));
				//ImGui::End();

				//m_ImGuiLayer->End();
			}
			//glfwSwapBuffers((GLFWwindow*)m_Window->GetNativeWindow());
			m_Window->OnUpdate();
		}
	}
}
