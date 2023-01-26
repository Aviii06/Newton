#include "IndexBuffer.h"
#include "Renderer.h"

namespace Vivid
{
	IndexBuffer::IndexBuffer(Vector<unsigned int>& indices)
	    : m_Count(indices.size())
	{
		GLCall(glGenBuffers(1, &m_RendererID)); // creating a buffer
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // binding the buffer
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(),
		    GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	Ref<IndexBuffer> IndexBuffer::Create(Vector<unsigned int>& indices)
	{
		return MakeRef<IndexBuffer>(indices);
	}
}
