#pragma once

#include "Transcendent-Engine/core/core.h"
#include "Transcendent-Engine/core/Timestep.h"
#include "Transcendent-Engine/Events/Event.h"

namespace TE {

	class Layer
	{
	public:
		Layer(const std::string& Name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
