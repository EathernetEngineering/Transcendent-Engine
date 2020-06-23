#pragma once
#include <Transcendent-Engine/Renderer/FrameBuffer.h>


namespace TE {
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		~OpenGLFrameBuffer();

		virtual void Invalidate() override;
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void UpdateSpecification(FrameBufferSpecification spec) override;
		const virtual FrameBufferSpecification& GetSpecification() const { return m_Specification; }
		virtual uint32_t GetColourAttachmentRendererID() const override { return m_ColourAttachment; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColourAttachment;
		uint32_t m_DepthAttachment;
		FrameBufferSpecification m_Specification;
	};
}
