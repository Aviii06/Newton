#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "utils/Error.h"
#include "glew-cmake/include/GL/glew.h"
#include <memory>

namespace Vivid
{
	class Renderer
	{
	private:
		Renderer() = default;

	public:
		static void Draw(Ref<VertexArray> va, unsigned int indexCount);
		static void DrawLine(Ref<VertexArray> va, unsigned int vertexCount);

		static void Clear();
	};

}