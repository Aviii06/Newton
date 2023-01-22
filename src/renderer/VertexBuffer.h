#pragma once

#include "common/Types.h"
#include "glm/glm/glm.hpp"

namespace NewtonRenderer
{

	struct Vertex
	{
		Vec3 position;
		Vec2 texcoord;
		Vec3 color;
		Vec3 normal;
	};

	class VertexBuffer
	{
	private:
		unsigned int m_RendererID;

	public:
		VertexBuffer(std::vector<Vertex>& vertices);

		~VertexBuffer();

		void Bind() const;

		void Unbind() const;
	};
}