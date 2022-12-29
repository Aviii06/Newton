#pragma once

#include "VertexBuffer.h"
#include "common/types.h"
#include <stddef.h>

namespace shape
{
	class quad3d;

	class sphere;
} // namespace shape

class shape::quad3d
{
private:
	float m_Size;
	Vector<Vertex> m_Pos;
	Vector<unsigned int> m_Ind;

public:
	quad3d(int size);

	Vector<Vertex>& getPositions();

	Vector<unsigned int>& getIndices();

	size_t getPositionsSize();

	size_t getIndicesSize();
};

class shape::sphere
{
private:
	float m_Radius;
	float m_Pos[8 * 8];
	unsigned int m_Ind[12 * 3];

public:
	sphere(int size);

	float* getPositions();

	unsigned int* getIndices();

	size_t getPositionsSize();

	size_t getIndicesSize();
};
