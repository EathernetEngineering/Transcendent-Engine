#include "tepch.h"
#include "Transcendent-Engine/Renderer/RenderCommand.h"

namespace TE {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
