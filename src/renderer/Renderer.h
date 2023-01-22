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
		static Renderer* s_Instance;
		Renderer() = default;

	public:
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader* shader) const;

		void Clear() const;
		static Renderer* GetInstance()
		{
			if (s_Instance == nullptr)
			{
				s_Instance = new Renderer();
			}
			return s_Instance;
		}
	};
}