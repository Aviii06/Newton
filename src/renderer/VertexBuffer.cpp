#include "VertexBuffer.h"
#include "Renderer.h"

namespace Vivid
{
	VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
	{
		GLCall(glGenBuffers(1, &m_RendererID)); // creating a buffer
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // binding the buffer
		GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	Ref<VertexBuffer> VertexBuffer::Create(std::vector<Vertex>& vertices)
	{
		return MakeRef<VertexBuffer>(vertices);
	}
}