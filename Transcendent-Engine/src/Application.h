#pragma once

namespace TE {
	class Application
	{
	public:
		virtual void run() = 0;
	};
	/* TO BE DEFINED BY CLIENT */
	Application* createApplication();
}


extern TE::Application* TE::createApplication();

int main(int argc, char* argv);
