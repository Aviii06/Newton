#pragma once
#include "common/Types.h"
#include "utils/Error.h"
#include "renderer/Renderer.h"
#include "renderer/Mesh.h"
#include "renderer/Camera.h"

namespace Vivid
{
	struct Storage
	{
		Ref<VertexArray> vao;
		Ref<Shader> quadShader;
		Ref<Shader> lineShader;
		Ref<Shader> ellipseShader;
		Vector<Vertex> quadVertices;
		Vector<unsigned int> quadIndices;
		Vector<Vertex> ellipseVertices;
		Vector<unsigned int> ellipseIndices;
		Vector<Vertex> lineVertices;
		Vector<unsigned int> lineIndices;
	};
	class Renderer2D
	{
	private:
		static Storage s_Storage;
		Renderer2D() = default;
		~Renderer2D() = default;
		static void drawQuad(Vec2 vertex1, Vec2 vertex2, Vec2 vertex3, Vec2 vertex4, Vec3 color);
		static void drawQuad(float x, float y, float width, float height, const Vec3& color);
		static void drawEllipse(Vec2 center, float radiusX, float radiusY, Vec3 color);
		static void drawLine(Vec2 vertex1, Vec2 vertex2, Vec2 vertex3, Vec2 vertex4, Vec3 color);

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene();
		static void EndScene();

		static void DrawQuad(float x, float y, float width, float height, const Vec3& color);
		static void DrawQuad(const Vec2& vertex1, const Vec2& vertex2, const Vec2& vertex3,
		    const Vec2& vertex4, const Vec3& color);

		static void DrawLine(Vec2 start, Vec2 end, float thickness, Vec3 color);

		static void DrawEllipse(Vec2 center, float radiusX, float radiusY, Vec3 color);
		static void DrawCircle(Vec2 center, float radius, Vec3 color);
	};
}
