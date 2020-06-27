#include <tepch.h>
#include <Transcendent-Engine/core/DebugLayer.h>
#include <ImGui.h>
#include <Transcendent-Engine/core/Application.h>

namespace TE 
{
	DebugLayer::DebugLayer(const std::string& DebugName) 
		: m_DebugName(DebugName), Layer(DebugName)
	{
	}

	void DebugLayer::OnImGuiRender()
	{
		ImGui::ShowMetricsWindow();

		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		if (ImGui::Button("Print current memory usage")) {
			TE_CORE_TRACE("Current heap memory usage is {0} with {1} allocations.", MemoryData::memattimeString()->c_str(), MemoryData::AllocationsAtTime());
		}
		if (ImGui::Button("Print Main viewport size")) {
			TE_CORE_TRACE("Main viewport is {0}x{1}.", (unsigned int)ImGui::GetMainViewport()->Size.x, (unsigned int)ImGui::GetMainViewport()->Size.y);
		}
		ImGui::End();
	}
}
