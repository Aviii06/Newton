#pragma once

#include "Shape.h"

namespace NewtonRenderer
{
	class Quad3d : public Shape
	{
	private:
		float m_Size;

	public:
		Quad3d(int size, Vec3 col = Vec3(1.0f, 1.0f, 1.0f));
	};
}
