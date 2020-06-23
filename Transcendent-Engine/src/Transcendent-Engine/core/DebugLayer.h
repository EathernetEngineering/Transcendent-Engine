#pragma once
#include <Transcendent-Engine/core/Layer.h>

namespace TE 
{
	class DebugLayer : public Layer
	{
	public:
		DebugLayer(const std::string& DebugName);

		void OnImGuiRender() override;

	protected:
		std::string m_DebugName;
	};
}
