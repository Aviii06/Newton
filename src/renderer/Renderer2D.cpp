#include "Renderer2D.h"

namespace NewtonRenderer
{

	Storage Renderer2D::s_Storage;
	void Renderer2D::Init()
	{
		s_Storage.quadShader = MakeRef<Shader>("./../assets/shaders/basic.vertexShader.glsl", "./../assets/shaders/basic.pixelShader.glsl");
		s_Storage.lineShader = MakeRef<Shader>("./../assets/shaders/basic.vertexShader.glsl", "./../assets/shaders/line.pixelShader.glsl");
		// Create vertices of a square
		Vertex squareVert1 = { { 0.0f, 100.0f, -20.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert2 = { { 100.0f, 100.0f, -20.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert3 = { { 100.0f, 0.0f, -20.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert4 = { { 0.0f, 0.0f, -20.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };

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

		s_Storage.vao = MakeRef<VertexArray>();
		s_Storage.vao->AddVertexBuffer(vb, layout);
		s_Storage.vao->AddIndexBuffer(ib);
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene()
	{
		Camera* camera = Camera::GetInstance();
		camera->SetPerspective(glm::ortho(-960.0f, 960.0f, -540.0f, 540.0f, 0.1f, 100.0f));

		s_Storage.quadShader->Bind();
		s_Storage.quadShader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		s_Storage.quadShader->SetUniformMat4f("u_View", camera->GetViewMatrix());
		s_Storage.quadShader->SetUniformMat4f("u_Proj", camera->GetProjectionMatrix());

		s_Storage.lineShader->Bind();
		s_Storage.lineShader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		s_Storage.lineShader->SetUniformMat4f("u_View", camera->GetViewMatrix());
		s_Storage.lineShader->SetUniformMat4f("u_Proj", camera->GetProjectionMatrix());
	}

	void Renderer2D::DrawQuad(float x, float y, float width, float height, const Vec3& color)
	{
		s_Storage.quadShader->Bind();
		drawQuadImpl(x, y, width, height, color);
	}

	void Renderer2D::DrawQuad(const Vec2& vertex1, const Vec2& vertex2, const Vec2& vertex3, const Vec2& vertex4, const Vec3& color)
	{
		s_Storage.quadShader->Bind();
		drawQuadImpl(vertex1.x, vertex1.y, vertex2.x - vertex1.x, vertex3.y - vertex1.y, color);
	}

	void Renderer2D::DrawLine(Vec2 start, Vec2 end, Vec3 color)
	{
		s_Storage.lineShader->Bind();
		drawQuadImpl(start.x, start.y, end.x - start.x, end.y - start.y, color);
	}

	// Todo: use batch rendering
	void Renderer2D::drawQuadImpl(float x, float y, float width, float height, const Vec3& color)
	{
		Vertex squareVert1 = { { x, y, -20.0f }, { 0.0f, 0.0f }, { color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert2 = { { x + width, y, -20.0f }, { 1.0f, 0.0f }, { color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert3 = { { x + width, y + height, -20.0f }, { 1.0f, 1.0f }, { color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex squareVert4 = { { x, y + height, -20.0f }, { 0.0f, 1.0f }, { color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };

		Vector<Vertex> verts = { squareVert1, squareVert2, squareVert3, squareVert4 };

		Vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		VertexBuffer vb(verts);
		IndexBuffer ib(indices);

		VertexBufferLayout layout;
		layout.AddFloat(3);
		layout.AddFloat(2);
		layout.AddFloat(3);
		layout.AddFloat(3);

		s_Storage.vao->AddVertexBuffer(vb, layout);
		s_Storage.vao->AddIndexBuffer(ib);

		Renderer::Draw(s_Storage.vao, ib.GetCount());
	}
}
