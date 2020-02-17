#include "../include/Transcendent-Engine.h"

class Sandbox : public TE::Application
{
public:
	void Run() override;
};

TE::Application* TE::createApplication() {
	return new Sandbox;
}

void Sandbox::Run() {
	while (true);
}
