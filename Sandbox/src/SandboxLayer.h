#pragma once

#include <Transcendent-Engine.h>

class SandboxLayer : public TE::Layer
{
public:
	SandboxLayer();
	~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(TE::Timestep ts) override;
	virtual void OnImGuiRender() override;

private:
	TE::OrthographicCamera* m_Camera = new TE::OrthographicCamera(0.0f, 1280.0f, 0.0f, 720.0f);

	float m_pos1[2]{ 0.0f, 0.0f }, m_pos2[2]{ 0.0f, 0.0f }, 
		  m_pos3[2]{ 0.0f, 0.0f }, m_pos4[2]{ 0.0f, 0.0f };

	float m_Scalef1 = 100.0f, m_Scalef2 = 100.0f, 
		  m_Scalef3 = 100.0f, m_Scalef4 = 100.0f;

	glm::vec2 m_Position1;
	glm::vec2 m_Scale1;
	glm::vec4 m_Colour1;

	glm::vec2 m_Position2;
	glm::vec2 m_Scale2;
	glm::vec4 m_Colour2;

	glm::vec2 m_Position3;
	glm::vec2 m_Scale3;
	glm::vec4 m_Colour3;

	glm::vec2 m_Position4;
	glm::vec2 m_Scale4;
	glm::vec4 m_Colour4;

	TE::FrameBufferSpecification* m_spec;
	TE::Ref<TE::FrameBuffer> m_FrameBufferObject;
};
