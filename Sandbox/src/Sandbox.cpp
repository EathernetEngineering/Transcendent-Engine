#include "tepch.h"
#include "../include/Transcendent-Engine.h"

class Sandbox : public TE::Application
{
public:
	Sandbox() = default;
};

TE::Application* TE::createApplication() {
	return new Sandbox;
}