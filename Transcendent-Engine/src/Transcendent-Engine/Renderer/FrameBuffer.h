#pragma once



namespace TE {

	struct FrameBufferSpecification 
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		const virtual FrameBufferSpecification& GetSpecification() const = 0;

		virtual void Invalidate() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void UpdateSpecification(FrameBufferSpecification spec) = 0;

		virtual uint32_t GetColourAttachmentRendererID() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};
}
