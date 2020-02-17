#pragma once

#include "Transcendent-Engine/Core/Core.h"
#include "Transcendent-Engine/Core/Timestep.h"
#include "Transcendent-Engine/Events/Event.h"

namespace TE {

	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
