#pragma once
#include "Transcendent-Engine/core/core.h"
#include "Transcendent-Engine/core/Window.h"
#include "Transcendent-Engine/core/Input.h"
#include "Transcendent-Engine/Events/Event.h"
#include "Transcendent-Engine/Events/ApplicationEvent.h"

int main(int argc, char** argv);

namespace TE {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		virtual void Run();
		virtual void OnEvent(Event& e);

		virtual bool OnWindowClose(WindowCloseEvent& e);
		virtual bool OnWindowResize(WindowResizeEvent& e);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow()       { return *m_Window;   }

	private:
		bool m_Running = true;
		bool m_Minimized = false;
	private:
		std::shared_ptr<Window> m_Window = nullptr;
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};
	/* TO BE DEFINED BY CLIENT */
	Application* createApplication();
}

extern TE::Application* TE::createApplication();
