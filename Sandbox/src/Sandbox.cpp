#include "../include/Transcendent-Engine.h"

class Sandbox : public TE::Application
{
public:
	void Run() override;
	void Get() override;
};

TE::Application* TE::createApplication() {
	return new Sandbox;
}

void Sandbox::Run() {
	while (true);
}
void Sandbox::Get() {
	while (true);
}