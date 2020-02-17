#pragma once

#include "Transcendent-Engine/core/Layer.h"

#include "Transcendent-Engine/Events/ApplicationEvent.h"
#include "Transcendent-Engine/Events/KeyEvent.h"
#include "Transcendent-Engine/Events/MouseEvent.h"

namespace TE {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_time = 0.0f;
	};
}
