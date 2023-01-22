#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "utils/Error.h"
#include "glew-cmake/include/GL/glew.h"
#include <memory>

namespace NewtonRenderer
{
	class Renderer
	{
	private:
		Renderer() = default;

	public:
		static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

		static void Clear();
	};

}