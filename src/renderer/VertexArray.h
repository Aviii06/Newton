#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace NewtonRenderer
{
	class VertexArray
	{
	private:
		unsigned int m_RendererID;

	public:
		VertexArray();
		~VertexArray();

		static Ref<VertexArray> Create();

		void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void AddIndexBuffer(const IndexBuffer& ib);

		void Bind() const;

		void Unbind() const;
	};
}