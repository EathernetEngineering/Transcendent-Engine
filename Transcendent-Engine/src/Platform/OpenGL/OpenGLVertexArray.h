#pragma once

#include "Transcendent-Engine/Renderer/VertexArray.h"
#include <glad/glad.h>

namespace TE {

	/*!
	 * Vertex arral implementation for OpenGL.
	 */
	class OpenGLVertexArray : public VertexArray
	{
	public:
		/*!
		 * Constructor for OpenGL vertex array class.
		 */
		OpenGLVertexArray();
		/*!
		 * Destructor for OpenGL vertex array class.
		 */
		virtual ~OpenGLVertexArray();

		/*!
		 * Bind the vertex array.
		 */
		virtual void Bind() const override;
		/*!
		 * Unbind the vertex array.
		 */
		virtual void Unbind() const override;

		/*!
		 * Add a vertex buffer to the vertex array.
		 * @param vertexBuffer shared_ptr to the vertex buffer to be added.
		 */
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		/*!
		 * Add a vertex buffer to the vertex array.
		 * @param indexBuffer shared_ptr to the index buffer to be added.
		 */
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		/*!
		 * Get the vector containg the vertex buffers.
		 * @return Vector with all vertex buffers in the array.
		 */
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		/*!
		 * Get the vector containg the index buffers.
		 * @return Vector with all index buffers in the array.
		 */
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

	/*!
	 * OpenGL implementation of vertex buffers.
	 */
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		/*!
		 * Constructor for OpenGL vertex buffer class.
		 * @param verticies The data to be used.
		 * @param size The total size of the verticies to be used.
		 */
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		/*!
		 * Destructor for OpenGL vertex buffer class.
		 */
		virtual ~OpenGLVertexBuffer();

		/*!
		 * Bind the vertex buffer.
		 */
		virtual void Bind() const override;
		/*!
		 * Unbind the vertex buffer.
		 */
		virtual void Unbind() const override;

		/*!
		 * Get the layout used by this vertex buffer.
		 * @retun [Vertex buffer layout](@ref BufferLayout) used by this vertex buffer. 
		 */
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		/*!
		 * Set the layout used by this vertex buffer.
		 * @param layout [Vertex buffer layout](@ref BufferLayout) to be used by this vertex buffer.
		 */
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	/*!
	 * OpenGL implementation of index buffers.
	 */
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		/*!
		 * Constructor for OpenGL index buffer class.
		 * @param indicies The data to be used.
		 * @param count The number of indicies to be used.
		 */
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		/*!
		 * Destructor for OpenGL index buffer class.
		 */
		virtual ~OpenGLIndexBuffer();


		/*!
		 * Bind the index buffer.
		 */
		virtual void Bind() const;
		/*!
		 * Unbind the index buffer.
		 */
		virtual void Unbind() const;

		/*!
		 * Get the count of indecies.
		 * @return 32 bit integer containing the count
		 */
		virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}
