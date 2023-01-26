#include "NewtonRenderer.h"

#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <math.h>

/* Function to linearly interpolate between a0 and a1
 * Weight w should be in the range [0.0, 1.0]
 */
float interpolate(float a0, float a1, float w)
{
	/* // You may want clamping by inserting:
	 * if (0.0 > w) return a0;
	 * if (1.0 < w) return a1;
	 */
	return (a1 - a0) * w + a0;
	/* // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
	 * return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
	 *
	 * // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
	 * return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
	 */
}

typedef struct
{
	float x, y;
} vector2;

/* Create pseudorandom direction vector
 */
vector2 randomGradient(int ix, int iy)
{
	// No precomputed gradients mean this works for any number of grid coordinates
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2; // rotation width
	unsigned a = ix, b = iy;
	a *= 3284157443;
	b ^= a << s | a >> w - s;
	b *= 1911520717;
	a ^= b << s | b >> w - s;
	a *= 2048419325;
	float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
	vector2 v;
	v.x = cos(random);
	v.y = sin(random);
	return v;
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y)
{
	// Get gradient from integer coordinates
	vector2 gradient = randomGradient(ix, iy);

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx * gradient.x + dy * gradient.y);
}

// Compute Perlin noise at coordinates x, y
float perlin(float x, float y)
{
	// Determine grid cell coordinates
	int x0 = (int)floor(x);
	int x1 = x0 + 1;
	int y0 = (int)floor(y);
	int y1 = y0 + 1;

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	// Interpolate between grid point gradients
	float n0, n1, ix0, ix1, value;

	n0 = dotGridGradient(x0, y0, x, y);
	n1 = dotGridGradient(x1, y0, x, y);
	ix0 = interpolate(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	ix1 = interpolate(n0, n1, sx);

	value = interpolate(ix0, ix1, sy);
	//	value = 1 / (1 + std::abs(std::sin(x) + std::sin(y)));
	return value * 0.5 + 0.5; // Will return in range -1 to 1. To make it in range 0 to 1, multiply by 0.5 and add 0.5
}

int GetState(const double& a, const double& b, const double& c, const double& d)
{
	int a1 = std::round(a);
	int b1 = std::round(b);
	int c1 = std::round(c);
	int d1 = std::round(d);

	return a1 * 8 + b1 * 4 + c1 * 2 + d1 * 1;
}

int main(void)
{
	Application* app = Application::GetInstance(1920, 1080, "Marching Squares");

	OPENGL_2D_CONFS

	int dim = 2;
	float dimPerlin = dim * 0.020735;

	Vivid::Renderer2D::Init();

	while (app->IsRunning())
	{
		Vivid::Renderer2D::BeginScene();

		for (int i = -1000 / dim; i <= 1000 / dim; i++)
		{
			for (int j = -1000 / dim; j <= 1000 / dim; j++)
			{
				double v1 = perlin(i * dimPerlin, j * dimPerlin);
				double v2 = perlin((i + 1) * dimPerlin, j * dimPerlin);
				double v3 = perlin((i + 1) * dimPerlin, (j + 1) * dimPerlin);
				double v4 = perlin(i * dimPerlin, (j + 1) * dimPerlin);

				int x = i * dim;
				int y = j * dim;

				Vec2 x1 = Vec2(x, y);
				Vec2 x2 = Vec2(x + dim, y);
				Vec2 x3 = Vec2(x + dim, y + dim);
				Vec2 x4 = Vec2(x, y + dim);

				Vivid::Renderer2D::DrawQuad(x1.x, x1.y, dim, dim, Vec3(v1, v1, v1));
				Vivid::Renderer2D::DrawQuad(x2.x, x2.y, dim, dim, Vec3(v2, v2, v2));
				Vivid::Renderer2D::DrawQuad(x3.x, x3.y, dim, dim, Vec3(v3, v3, v3));
				Vivid::Renderer2D::DrawQuad(x4.x, x4.y, dim, dim, Vec3(v4, v4, v4));

				Vec2 a = x1 + (x2 - x1) * (v1 / (v1 + v2));
				Vec2 b = x2 + (x3 - x2) * (v2 / (v2 + v3));
				Vec2 c = x3 + (x4 - x3) * (v3 / (v3 + v4));
				Vec2 d = x4 + (x1 - x4) * (v4 / (v4 + v1));

				Vec3 col = Vec3(1.0f, 0.0f, 0.0f);
				float thickness = 1.0f;
				switch (GetState(v1, v2, v3, v4))
				{
				case 1:
					Vivid::Renderer2D::DrawLine(c, d, thickness, col);
					break;
				case 2:
					Vivid::Renderer2D::DrawLine(b, c, thickness, col);
					break;
				case 3:
					Vivid::Renderer2D::DrawLine(b, d, thickness, col);
					break;
				case 4:
					Vivid::Renderer2D::DrawLine(a, b, thickness, col);
					break;
				case 5:
					Vivid::Renderer2D::DrawLine(a, d, thickness, col);
					Vivid::Renderer2D::DrawLine(b, c, thickness, col);
					break;
				case 6:
					Vivid::Renderer2D::DrawLine(a, c, thickness, col);
					break;
				case 7:
					Vivid::Renderer2D::DrawLine(a, d, thickness, col);
					break;
				case 8:
					Vivid::Renderer2D::DrawLine(d, a, thickness, col);
					break;
				case 9:
					Vivid::Renderer2D::DrawLine(c, a, thickness, col);
					break;
				case 10:
					Vivid::Renderer2D::DrawLine(a, b, thickness, col);
					Vivid::Renderer2D::DrawLine(c, d, thickness, col);
					break;
				case 11:
					Vivid::Renderer2D::DrawLine(a, b, thickness, col);
					break;
				case 12:
					Vivid::Renderer2D::DrawLine(b, d, thickness, col);
					break;
				case 13:
					Vivid::Renderer2D::DrawLine(b, c, thickness, col);
					break;
				case 14:
					Vivid::Renderer2D::DrawLine(d, c, thickness, col);
					break;
				}
			}
		}

		Vivid::Renderer2D::EndScene();

		app->GetWindow().Update();
	}
}
