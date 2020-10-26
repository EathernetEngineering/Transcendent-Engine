#pragma once
#include "Transcendent-Engine/core/core.h"

#include "Transcendent-Engine/core/Input.h"
#include "Transcendent-Engine/Events/Event.h"
#include "Transcendent-Engine/Events/ApplicationEvent.h"

#include "Transcendent-Engine/core/LayerStack.h"
#include "Transcendent-Engine/ImGui/ImGuiLayer.h"

#if defined _DEBUG
	#include "Transcendent-Engine/core/DebugLayer.h"
#endif

#include "Transcendent-Engine/core/Window.h"

#include "imgui.h"

namespace MemoryAllocInfo {
	extern size_t memalloc;
	extern size_t memfree;
	extern size_t memattime();
}

int main(int argc, char** argv);

namespace TE {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		virtual void Run();
		virtual void OnEvent(Event& e);

		virtual void PushLayer(Layer* layer);
		virtual void PushOverlay(Layer* overlay);

		virtual bool OnWindowClose(WindowCloseEvent& e);
		virtual bool OnWindowResize(WindowResizeEvent& e);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow()       { return *m_Window;   }

	private:
		Ref<Window> m_Window = nullptr;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		#if defined _DEBUG
			Layer* m_DebugLayer;
		#endif
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};
	/* TO BE DEFINED BY CLIENT */
	Application* createApplication();
}

extern TE::Application* TE::createApplication();
