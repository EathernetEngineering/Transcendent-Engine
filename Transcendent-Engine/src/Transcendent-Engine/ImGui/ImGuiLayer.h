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

	private:
		float m_Time = 0.0f;
	};
}
