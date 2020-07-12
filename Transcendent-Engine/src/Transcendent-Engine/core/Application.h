#pragma once
#include "Transcendent-Engine/core/core.h"

#include "Transcendent-Engine/core/Input.h"
#include "Transcendent-Engine/Events/Event.h"
#include "Transcendent-Engine/Events/ApplicationEvent.h"

#include "Transcendent-Engine/core/LayerStack.h"
#include "Transcendent-Engine/ImGui/ImGuiLayer.h"

#if defined TE_DEBUG
	#include "Transcendent-Engine/core/DebugLayer.h"
#endif

#include "Transcendent-Engine/core/Window.h"

#include "Transcendent-Engine/core/Timestep.h"

#include "imgui.h"

struct MemoryData
{
	static uint32_t Allocations;
	static uint32_t Deletions;
	static uint32_t memalloc;
	static uint32_t memfree;
	static uint32_t AllocationsAtTime();
	static uint32_t memattime();
	static std::shared_ptr<std::string> memattimeString();
	static std::shared_ptr<std::string> TotalMemoryString();
};

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
		std::shared_ptr<Window> m_Window = nullptr;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastFrameTime;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		#if defined TE_DEBUG
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
