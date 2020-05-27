#pragma once

#include <Transcendent-Engine.h>

class SandboxLayer : public TE::Layer
{
public:
	SandboxLayer();
	~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;

private:
	TE::OrthographicCamera* m_Camera = new TE::OrthographicCamera(0.0f, 1280.0f, 0.0f, 720.0f);

	glm::vec2 m_Position1;
	glm::vec2 m_Scale1;
	glm::vec4 m_Colour1;

	glm::vec2 m_Position2;
	glm::vec2 m_Scale2;
	glm::vec4 m_Colour2;
};
