#pragma once

namespace TE {

	class IndexBuffer
	{
	public:
		IndexBuffer(const unsigned* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const { return m_count; }

	private:
		unsigned m_RendererID;
		unsigned m_count;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void Unbind() const;

	private:
		unsigned m_RendererID;
	};

	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		GLboolean normalized;

		static unsigned int GetSizeOfType(unsigned int type) {
			switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
			}
			TE_CORE_ASSERT(false, "Invalid type");
			return 0;
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();

		template<typename T>
		void Push(unsigned int count) { static_assert(false); }

		template<>
		void Push<float>(unsigned int count) {
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}
		template<>

		void Push<unsigned int>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}
		template<>

		void Push<unsigned char>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
		inline GLsizei GetStride() const { return m_Stride; }

	private:
		std::vector<VertexBufferElement> m_Elements;
		GLsizei m_Stride;
	};

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int m_RendererID;
	};
}
