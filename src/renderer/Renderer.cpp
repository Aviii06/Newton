#include "Renderer.h"

namespace NewtonRenderer
{
	void Renderer::Draw(Ref<VertexArray> va, unsigned int indexCount)
	{
		va->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Renderer::DrawLine(Ref<VertexArray> va, unsigned int vertexCount)
	{
		va->Bind();

		GLCall(glLineWidth(1.0f));
		GLCall(glDrawArrays(GL_LINES, 0, vertexCount));
	}
}