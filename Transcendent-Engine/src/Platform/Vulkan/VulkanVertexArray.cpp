#include <tepch.h>
#include <Platform/Vulkan/VulkanVertexArray.h>

namespace TE {

	// **********************************************************************************
	// ***** Vertex Array ***************************************************************
	// **********************************************************************************
	VulkanVertexArray::VulkanVertexArray()
	{

	}

	VulkanVertexArray::~VulkanVertexArray()
	{

	}

	void VulkanVertexArray::Bind() const
	{

	}

	void VulkanVertexArray::Unbind() const
	{

	}

	void VulkanVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{

	}

	void VulkanVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{

	}

	// **********************************************************************************
	// ***** Vertex Buffer **************************************************************
	// **********************************************************************************
	VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, size_t size)
	{

	}
	
	VulkanVertexBuffer::VulkanVertexBuffer(size_t size)
	{

	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{

	}

	void VulkanVertexBuffer::Bind() const
	{

	}

	void VulkanVertexBuffer::Unbind() const
	{

	}

	// **********************************************************************************
	// ***** Index Buffer ***************************************************************
	// **********************************************************************************
	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* vertices, size_t size)
	{

	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{

	}

	void VulkanIndexBuffer::Bind() const
	{

	}

	void VulkanIndexBuffer::Unbind() const
	{

	}

}
