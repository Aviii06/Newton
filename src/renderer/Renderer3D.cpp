#include "Renderer3D.h"
#include "Camera.h"

namespace Vivid
{
	Storage3D Renderer3D::s_Storage3D;
	void Renderer3D::Init()
	{
		s_Storage3D.quadShader = MakeRef<Shader>("./../assets/shaders/quad.vertexShader.glsl",
		    "./../assets/shaders/quad.pixelShader.glsl");
		Vertex squareVert1 = { { 0.0f, 100.0f, -20.0f }, { 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert2 = { { 100.0f, 100.0f, -20.0f }, { 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert3 = { { 100.0f, 0.0f, -20.0f }, { 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert4 = { { 0.0f, 0.0f, -20.0f }, { 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };

		Vector<Vertex> verts = { squareVert1, squareVert2, squareVert3, squareVert4 };

		Vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		VertexBuffer vb(verts);
		VertexBufferLayout layout;
		layout.AddFloat(3); // Position
		layout.AddFloat(2); // Texcoord
		layout.AddFloat(3); // Color
		layout.AddFloat(3); // Normal

		IndexBuffer ib(indices);

		s_Storage3D.vao = MakeRef<VertexArray>();
		s_Storage3D.vao->AddVertexBuffer(vb, layout);
		s_Storage3D.vao->AddIndexBuffer(ib);

		s_Storage3D.quadVertices.reserve(100000);
	}

	void Renderer3D::BeginScene()
	{
		Camera* camera = Camera::GetInstance();

		s_Storage3D.quadShader->Bind();
		s_Storage3D.quadShader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		s_Storage3D.quadShader->SetUniformMat4f("u_View", camera->GetViewMatrix());
		s_Storage3D.quadShader->SetUniformMat4f("u_Proj", camera->GetProjectionMatrix());
	}

	void Renderer3D::EndScene()
	{
		if (!s_Storage3D.quadVertices.empty())
		{
			VertexBuffer vb(s_Storage3D.quadVertices);
			IndexBuffer ib(s_Storage3D.quadIndices);

			VertexBufferLayout layout;
			layout.AddFloat(3);
			layout.AddFloat(2);
			layout.AddFloat(3);
			layout.AddFloat(3);

			s_Storage3D.vao->AddVertexBuffer(vb, layout);
			s_Storage3D.vao->AddIndexBuffer(ib);

			// Draw call
			s_Storage3D.quadShader->Bind();
			Renderer::Draw(s_Storage3D.vao, ib.GetCount());

			s_Storage3D.quadVertices.clear();
			s_Storage3D.quadIndices.clear();
		}
	}

	void Renderer3D::DrawQuad(Vec3 vertex1, Vec3 vertex2, Vec3 vertex3, Vec3 vertex4, Vec3 color)
	{
		Vertex quadVert1 = { { vertex1.x, vertex1.y, vertex1.z }, { 0.0f, 0.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex quadVert2 = { { vertex2.x, vertex2.y, vertex2.z }, { 1.0f, 0.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex quadVert3 = { { vertex3.x, vertex3.y, vertex3.z }, { 1.0f, 1.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex quadVert4 = { { vertex4.x, vertex4.y, vertex4.z }, { 0.0f, 1.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };

		Vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		// Indices
		s_Storage3D.quadIndices.emplace_back(s_Storage3D.quadVertices.size()); // 0
		s_Storage3D.quadIndices.emplace_back(s_Storage3D.quadVertices.size() + 1); // 1
		s_Storage3D.quadIndices.emplace_back(s_Storage3D.quadVertices.size() + 2); // 2
		s_Storage3D.quadIndices.emplace_back(s_Storage3D.quadVertices.size() + 2); // 2
		s_Storage3D.quadIndices.emplace_back(s_Storage3D.quadVertices.size() + 3); // 3
		s_Storage3D.quadIndices.emplace_back(s_Storage3D.quadVertices.size()); // 0

		// Vertices
		s_Storage3D.quadVertices.emplace_back(quadVert1);
		s_Storage3D.quadVertices.emplace_back(quadVert2);
		s_Storage3D.quadVertices.emplace_back(quadVert3);
		s_Storage3D.quadVertices.emplace_back(quadVert4);
	}
}
