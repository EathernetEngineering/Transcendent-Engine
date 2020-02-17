#pragma once
#include "Transcendent-Engine/core/core.h"

#include "Transcendent-Engine/core/Window.h"

namespace TE {
	class Application
	{
	public:
		virtual void Run() = 0;

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};
	/* TO BE DEFINED BY CLIENT */
	Application* createApplication();
}


extern TE::Application* TE::createApplication();

int main(int argc, char** argv);
