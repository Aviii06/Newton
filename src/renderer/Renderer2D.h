#pragma once
#include "common/Types.h"
#include "utils/Error.h"
#include "renderer/Renderer.h"
#include "renderer/Mesh.h"
#include "renderer/Camera.h"

namespace NewtonRenderer
{
	struct Storage
	{
		Ref<VertexArray> vao;
		Ref<Shader> quadShader;
		Ref<Shader> lineShader;
	};
	class Renderer2D
	{
	private:
		static Storage s_Storage;
		Renderer2D() = default;
		~Renderer2D() = default;
		static void drawQuadImpl(float x, float y, float width, float height, const Vec3& color);

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene();
		static void EndScene();

		static void DrawQuad(float x, float y, float width, float height, const Vec3& color);
		static void DrawQuad(const Vec2& vertex1, const Vec2& vertex2, const Vec2& vertex3, const Vec2& vertex4, const Vec3& color);

		static void DrawLine(Vec2 start, Vec2 end, Vec3 color);
	};
}