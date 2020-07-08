#pragma once
#include <Transcendent-Engine/Renderer/FrameBuffer.h>


namespace TE {

	/*!
	 * OpenGL Framebuffer. This is the class used for the OpenGL impementation of frame buffers. [Base frame buffer class.](@ref FrameBuffer)
	 */

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:

		/*!
		 * Constructor for OpenGL frame buffer class
		 * Takes in a [FrameBufferSpecification](@ref FrameBufferSpecififcation) and initializes the frame buffer.
		 * @param spec specification for the frame buffer.
		 */
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);

		/*!
		 * Destructor for OpenGL frame buffer class.
		 * Deletes the frame buffer.
		 */
		~OpenGLFrameBuffer();


		/*!
		 * Reinitalizes the class
		 */
		virtual void Invalidate() override;

		/*!
		 * Binds the frame buffer.
		 */
		virtual void Bind() override;

		/*!
		 * Unbinds the frame buffer.
		 */
		virtual void Unbind() override;


		/*!
		 * Updates the frame buffer specification.
		 * Should call Invalidate() after this.
		 * @param spec New specification for the class 
		 */
		virtual void UpdateSpecification(FrameBufferSpecification spec) override;

		/*!
		 * Returns specification the class is using.
		 * @return Specification of this frame buffer.
		 */
		const virtual FrameBufferSpecification& GetSpecification() const { return m_Specification; }

		/*!
		 * Retuns the OpenGL RendererID of the colour attachment.
		 * @return 32 bit unsigned integer, OpenGL renderer ID of the colour attacment.
		 */
		virtual uint32_t GetColourAttachmentRendererID() const override { return m_ColourAttachment; }

	private:

		/*!
		 * OpenGL renderer ID of framebuffer.
		 */
		uint32_t m_RendererID;

		/*!
		 * OpenGL renderer ID of colour attachment.
		 */
		uint32_t m_ColourAttachment;

		/*!
		 * OpenGL renderer ID of depth attachment.
		 */
		uint32_t m_DepthAttachment;


		/*!
		 * Frame buffer specification.
		 */
		FrameBufferSpecification m_Specification;
	};
}
