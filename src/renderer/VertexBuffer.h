#ifndef vertexbuffer
#define vertexbuffer

#include "../common/types.h"
#include "glm/glm/glm.hpp"

// Structure to standardize the vertices used in the meshes
struct Vec3
{
	float x, y, z;
	Vec3()
	    : x(0.0f)
	    , y(0.0f)
	    , z(0.0f)
	{
	}
	Vec3(float x, float y, float z)
	    : x(x)
	    , y(y)
	    , z(z)
	{
	}
	Vec3 operator*(float scalar) { return Vec3(x * scalar, y * scalar, z * scalar); }
};

struct Vec2
{
	float x, y;
	Vec2()
	    : x(0.0f)
	    , y(0.0f)
	{
	}
	Vec2(float x, float y)
	    : x(x)
	    , y(y)
	{
	}
	Vec2 operator*(float scalar) { return Vec2(x * scalar, y * scalar); }
};

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

#endif
