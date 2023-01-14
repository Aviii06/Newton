#pragma once

// Vector
#include <string>
#include <vector>
#include <memory>

template <class T>
using Vector = std::vector<T>;

/// std::unique_ptr
template <class T>
using Ptr = std::unique_ptr<T>;
/// std::shared_ptr
template <class T>
using Ref = std::shared_ptr<T>;
/// std::weak_ptr
template <class T>
using Weak = std::weak_ptr<T>;

// OPEN GL
#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_2_BYTES 0x1407
#define GL_3_BYTES 0x1408
#define GL_4_BYTES 0x1409
#define GL_DOUBLE 0x140A

#define GL_FALSE 0
#define GL_TRUE 1

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
