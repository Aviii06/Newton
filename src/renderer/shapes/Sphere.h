#pragma once

#include "Shape.h"

class Sphere : public Shape
{
private:
	float m_Radius;

public:
	Sphere(int radius);
};
