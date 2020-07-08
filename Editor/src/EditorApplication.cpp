#include "tepch.h"
#include "Transcendent-Engine.h"
#include "Transcendent-Engine/core/EntryPoint.h"
#include "ImGuiUILayer.h"

class Editor : public TE::Application
{
public:
	Editor() { PushLayer(new ImGuiUILayer("UI Window")); }
};

TE::Application* TE::createApplication() {
	return new Editor();
}