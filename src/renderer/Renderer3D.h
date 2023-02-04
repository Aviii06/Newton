#include "Renderer.h"

namespace Vivid
{
	struct Storage3D
	{
		Ref<VertexArray> vao;
		Ref<Shader> quadShader;
		Vector<Vertex> quadVertices;
		Vector<unsigned int> quadIndices;
		Ref<Shader> triangleShader;
		Vector<Vertex> triangleVertices;
		Vector<unsigned int> triangleIndices;
	};
	class Renderer3D
	{
	private:
		static Storage3D s_Storage3D;

	public:
		Renderer3D() = default;
		~Renderer3D() = default;

		static void Init();
		static void BeginScene();
		static void EndScene();

		static void DrawQuad(Vec3 vertex1, Vec3 vertex2, Vec3 vertex3, Vec3 vertex4, Vec3 color);
		static void DrawTriangle(Vec3 vertex1, Vec3 vertex2, Vec3 vertex3, Vec3 color);
		static void DrawCube(Vec3 center, float edgeLength, Vec3 color);
	};

}
