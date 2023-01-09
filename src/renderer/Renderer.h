#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "../utils/error.h"
#include "glew-cmake/include/GL/glew.h"
#include <memory>

class Renderer
{
private:
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

	void Clear() const;
};
