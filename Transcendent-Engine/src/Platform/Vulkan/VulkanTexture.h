#pragma once

#include <Transcendent-Engine/Renderer/Texture.h>

namespace TE {

	class VulkanTexture2D : public Texture2D
	{
	public:
		VulkanTexture2D(uint32_t Width, uint32_t Height) {}
		VulkanTexture2D(const std::string& Filepath) {}

		uint32_t GetWidth() const { return 0u; }
		uint32_t GetHeight() const { return 0u; }

		void SetData(void* data, uint32_t size) {}

		void Bind(uint32_t slot = 0) const {}
	};

}
