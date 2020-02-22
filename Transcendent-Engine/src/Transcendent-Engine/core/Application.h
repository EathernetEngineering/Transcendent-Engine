#pragma once
#include "Transcendent-Engine/core/core.h"
#include "Transcendent-Engine/core/Window.h"

int main(int argc, char** argv);

namespace TE {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		virtual void Run();

		inline static Application& Get() { return *s_Instance; }

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
