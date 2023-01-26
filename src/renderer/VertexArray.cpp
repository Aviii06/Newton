#include "VertexArray.h"

namespace Vivid
{
	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_RendererID));
		GLCall(glBindVertexArray(m_RendererID));
	}

	VertexArray::~VertexArray()
	{
	}

	void VertexArray::AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const Vector<VertexBufferElement> elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const VertexBufferElement element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(),
			    (const void*)offset));
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}

	void VertexArray::AddIndexBuffer(const IndexBuffer& ib)
	{
		Bind();
		ib.Bind();
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

	Ref<VertexArray> VertexArray::Create()
	{
		return MakeRef<VertexArray>();
	};
}