#include "tepch.h"
#include "Transcendent-Engine.h"
#include "Transcendent-Engine/core/EntryPoint.h"
#include "SandboxLayer.h"

class Sandbox : public TE::Application
{
public:
	Sandbox() { PushLayer(new SandboxLayer()); }
};

TE::Application* TE::createApplication() {
	return new Sandbox;
}