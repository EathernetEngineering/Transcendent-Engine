#pragma once

#include "Transcendent-Engine.h"

class SandboxLayer : public TE::Layer
{
public:
	SandboxLayer();
	~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;
};
