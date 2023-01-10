#pragma once

#include "Shape.h"

class Quad3d : public Shape
{
private:
	float m_Size;

public:
	Quad3d(int size, glm::vec3 col = glm::vec3(1.0f, 1.0f, 1.0f));
};
