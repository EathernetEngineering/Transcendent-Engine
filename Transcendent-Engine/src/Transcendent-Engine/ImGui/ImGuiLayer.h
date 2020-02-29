#pragma once

#include "Transcendent-Engine/core/Layer.h"

namespace TE {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void OnImGuiRender() override;
		void End();
		
		void SetShowDemoWindow(bool open) { m_ShowDemoWindow = open; }
		void SetShowAboutWindow(bool open) { m_ShowAboutWindow = open; }

	private:
		bool m_ShowDemoWindow = true;
		bool m_ShowAboutWindow = true;
		float m_Time = 0.0f;
	};
}
