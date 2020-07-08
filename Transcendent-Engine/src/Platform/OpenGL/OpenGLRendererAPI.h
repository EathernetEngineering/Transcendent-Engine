#pragma once

#include "Transcendent-Engine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace TE {

	/*!
	 * OpenGLRendererAPI is the api used for rendering with OpenGL. [Base class.](@ref RendererAPI)
	 */
	class OpenGLRendererAPI : public RendererAPI
	{
		/*!
		 * Initialzies the API
		 */
		void Init();

		/*!
		 * [Sets the viewport.](docs.gl/gl4/glViewport)
		 * @param x 32 bit unsigned integer that set the x value for the bottom right corner.
		 * @param y 32 bit unsigned integer that set the y value for the bottom right corner.
		 * @param width 32 bit unsigned integer that set the width from the bottom right corner.
		 * @param height 32 bit unsigned integer that set the height from the bottom right corner.
		 */
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		/*!
		 * Sets the clear colour of the current framebuffer.
		 * @param color vec4 representing the colour you wish to be set in the form of RGBA.
		 */
		void SetClearColor(const glm::vec4& color);

		/*!
		 * clears the colour buffer bit and the depth buffer bit.
		 */
		void Clear();

		/*!
		 * Draws the passed in vertex array.
		 * @see OpenGLVertexArray
		 * @param VertexArray [Vertex array](@Ref VertexArray) that contains the [verticies](@ref VertexBuffer) and [indicies](@Ref IndexBuffer) you wiuish to be drawn.
		 */
		void DrawIndexed(const Ref<VertexArray>& VertexArray);
	};
}
