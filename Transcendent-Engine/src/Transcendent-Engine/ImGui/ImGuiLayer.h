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

		virtual void OnAttach();
		virtual void OnDetach();

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}
