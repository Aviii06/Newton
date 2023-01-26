#pragma once

#include "Shape.h"

namespace Vivid
{
	class Sphere : public Shape
	{
	private:
		float m_Radius;

	public:
		Sphere(int radius);
	};
}