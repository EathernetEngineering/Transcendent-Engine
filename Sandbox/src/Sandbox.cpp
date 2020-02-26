#include "tepch.h"
#include "Transcendent-Engine.h"
#include "Transcendent-Engine/core/EntryPoint.h"
#include "SandboxLayer.h"

class Sandbox : public TE::Application
{
public:
	Sandbox() = default;
};

TE::Application* TE::createApplication() {
	return new Sandbox;
}