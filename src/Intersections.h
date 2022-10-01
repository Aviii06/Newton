#pragma once
#include <glm/glm.hpp>
#include "VertexBuffer.h"

#define ERROR_TOLERANCE  0.00000001

struct Ray {
	glm::vec3 ori;			// Origin
	glm::vec3 dir;			// Direction of the ray
};

struct Intersection
{
	double t;               // parameter of ray at point of intersection
	glm::vec3 P;            // location of hitpoint
	glm::vec3 N;            // normal vector at hitpoint
};

Intersection* make_intersection()
{
	Intersection* inter;

	inter = (Intersection*)malloc(sizeof(Intersection));

	return inter;
}

Intersection* intersect_ray_triangle(Ray* ray, const glm::vec3& V0, const glm::vec3& V1, const glm::vec3& V2)
{
	glm::vec3    u, v, n;
	glm::vec3    r, d;
	float   a, b;
	float t;
	glm::vec3 intersection;

	// get triangle edge vectors and plane normal

	u = V1 - V0;
	v = V2 - V0;
	n = cross(u, v);
	if (n.x == 0 && n.y == 0 && n.z == 0)            // triangle is degenerate; do not deal with this case
		return NULL;

	d = ray->ori - V0;
	a = -dot(n, d);
	b = dot(n, ray->dir);

	if (fabs(b) < ERROR_TOLERANCE) {     // ray is parallel to triangle plane
		if (a == 0)                  // case 1: ray lies in triangle plane
			return NULL;
		else return NULL;               // case 2: ray disjoint from plane
	}

	// get intersect point of ray with triangle plane

	t = a / b;
	if (t < ERROR_TOLERANCE)                   // triangle is behind/too close to ray => no intersect
		return NULL;                 // for a segment, also test if (t > 1.0) => no intersect

	// intersect point of ray and plane

	intersection = t * (ray->dir + ray->ori);

	// is I inside T?

	float    uu, uv, vv, du, dv, D;
	uu = dot(u, u);
	uv = dot(u, v);
	vv = dot(v, v);
	d  = intersection - V0;
	du = dot(d, u);
	dv = dot(d, v);
	D = uv * uv - uu * vv;

	// get and test parametric (i.e., barycentric) coords

	float p, q;  // were s, t in original code
	p = (uv * dv - vv * du) / D;
	if (p < 0.0 || p > 1.0)        // I is outside T
		return NULL;
	q = (uv * du - uu * dv) / D;
	if (q < 0.0 || (p + q) > 1.0)  // I is outside T
		return NULL;

	Intersection* inter = make_intersection();
	inter->t = t;
	inter->P = intersection;
	return inter;                      // I is in T
}

Ray* make_ray(Vertex v, const glm::vec3& lightPos)
{
	Ray* r = (Ray*)malloc(sizeof(Ray));
	r->ori.x = lightPos.x;
	r->ori.y = lightPos.y;
	r->ori.z = lightPos.z;
	r->dir = v.position - lightPos;  // IDK about this
	return r;
}

void createLitVector(Vector<Vertex>& vertices, glm::vec3 lightPos)
{

	for (auto v : vertices)
	{
		Ray* r = make_ray(v, lightPos);
		for (int i = 0; i < vertices.size() - 2; i+=3)
		{
			Intersection* intersection = intersect_ray_triangle(r, vertices[i].position, vertices[i + 1].position, vertices[i + 2].position);

			if (intersection == NULL)
			{
				vertices[i].isLit = 1.0f;
			}
			else
			{
				vertices[i].isLit = 0.0f;
			}
		}
	}
}