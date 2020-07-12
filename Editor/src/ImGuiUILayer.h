#pragma once

#include <Transcendent-Engine.h>

class ImGuiUILayer : public TE::Layer
{
public:
	ImGuiUILayer(const std::string& DebugName);
	~ImGuiUILayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(TE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(TE::Event& e) override;

private:
	TE::OrthographicCamera* m_Camera;
	TE::OrthographicCamera* m_GameCamera;

	TE::FrameBufferSpecification* m_Spec;
	TE::Ref<TE::FrameBuffer> m_FrameBufferObject;
	TE::Ref<TE::FrameBuffer> m_GameFrameBufferObject;

	bool m_SceneOpen = true;

protected:
	std::string m_DebugName;
};
