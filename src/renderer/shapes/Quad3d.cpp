#include "Quad3d.h"

namespace Vivid
{
	// TODO: Use multiple vertices to have correct normals for each vertex
	Quad3d::Quad3d(int size, Vec3 col)
	{
		m_Size = (float)size;
		const float const_Size = m_Size;

		// TODO: Correct culling
		Vec3 pos[8] = {
			Vec3(-const_Size, const_Size, -const_Size),
			Vec3(const_Size, const_Size, -const_Size),
			Vec3(-const_Size, -const_Size, -const_Size),
			Vec3(const_Size, -const_Size, -const_Size),
			Vec3(-const_Size, const_Size, const_Size),
			Vec3(const_Size, const_Size, const_Size),
			Vec3(-const_Size, -const_Size, const_Size),
			Vec3(const_Size, -const_Size, const_Size),
		};

		Vec2 tex[8] = {
			Vec2(0.0, 0.0),
			Vec2(1.0, 0.0),
			Vec2(1.0, 1.0),
			Vec2(0.0, 1.0),
			Vec2(0.0, 0.0),
			Vec2(1.0, 0.0),
			Vec2(1.0, 1.0),
			Vec2(0.0, 1.0),
		};

		Vec3 color[8] = {
			col,
			col,
			col,
			col,
			col,
			col,
			col,
			col,
		};

		Vec3 normal[8] = {
			Vec3(1.0, 1.0, 1.0),
			Vec3(1.0, 1.0, 1.0),
			Vec3(1.0, 1.0, 1.0),
			Vec3(1.0, 1.0, 1.0),
			Vec3(1.0, 1.0, 1.0),
			Vec3(1.0, 1.0, 1.0),
			Vec3(1.0, 1.0, 1.0),
			Vec3(1.0, 1.0, 1.0),
		};

		unsigned int ind[12 * 3] = {
			0, 1, 2, // Side 0
			2, 1, 3,
			4, 0, 6, // Side 1
			6, 0, 2,
			7, 5, 6, // Side 2
			6, 5, 4,
			3, 1, 7, // Side 3
			7, 1, 5,
			4, 5, 0, // Side 4
			0, 5, 1,
			3, 7, 2, // Side 5
			2, 7, 6
		};

		m_Pos.resize(8, Vertex());
		m_Ind.resize(12 * 3, int());

		for (int i = 0; i < 8; i++)
		{
			m_Pos[i].position = pos[i];
			m_Pos[i].texcoord = tex[i];
			m_Pos[i].color = color[i];
			m_Pos[i].normal = normal[i];
		}

		int i = 0;
		for (auto x : ind)
		{
			m_Ind[i] = x;
			i++;
		}
	}
}