#include "../include/Transcendent-Engine.h"

class Sandbox : public TE::Application
{
public:
	void run() override;
};

TE::Application* TE::createApplication() {
	return new Sandbox;
}

void Sandbox::run() {
	while (true);
}