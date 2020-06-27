#pragma once

#include "Transcendent-Engine/Renderer/Texture.h"

#include <glad/glad.h>

namespace TE {

	/*!
	 * OpenGL 2D texture API.
	 */
	class OpenGLTexture2D : public Texture2D
	{
	public:
		/*!
		 * Constructor for class.
		 * @param width The width of the texture.
		 * @param height The height of the texture.
		 */
		OpenGLTexture2D(uint32_t width, uint32_t height);
		/*!
		 * Constructor for class.
		 * @param path The file path of the texture.
		 */
		OpenGLTexture2D(const std::string& path);
		/*!
		 * Destructor for class.
		 */
		virtual ~OpenGLTexture2D();

		/*!
		 * Get the wdith.
		 * @return The width of the texture.
		 */
		virtual uint32_t GetWidth() const override { return m_Width; }
		/*!
		 * Get the height.
		 * @return The height of the texture.
		 */
		virtual uint32_t GetHeight() const override { return m_Height; }

		/*!
		 * Set the texture data.
		 * @param data The data to be set as a texture.
		 * @param size The size of the data.
		 */
		virtual void SetData(void* data, uint32_t size) override;

		/*!
		 * Bind the texture
		 */
		virtual void Bind(uint32_t slot = 0) const override;
	
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}
