#include "Renderer.h"

namespace Vivid
{
	struct Storage3D
	{
		Ref<VertexArray> vao;
		Ref<Shader> quadShader;
		Vector<Vertex> quadVertices;
		Vector<unsigned int> quadIndices;
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
	};
}

