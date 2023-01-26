#include "Renderer2D.h"

namespace Vivid
{

	Storage Renderer2D::s_Storage;
	void Renderer2D::Init()
	{
		// Initialize shaders
		s_Storage.quadShader = MakeRef<Shader>("./../assets/shaders/quad.vertexShader.glsl",
		    "./../assets/shaders/quad.pixelShader.glsl");
		s_Storage.lineShader = MakeRef<Shader>("./../assets/shaders/quad.vertexShader.glsl",
		    "./../assets/shaders/line.pixelShader.glsl");
		s_Storage.ellipseShader = MakeRef<Shader>("./../assets/shaders/quad.vertexShader.glsl",
		    "./../assets/shaders/ellipse.pixelShader.glsl");
		// Create vertices of a square
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

		s_Storage.ellipseShader->Bind();
		s_Storage.ellipseShader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		s_Storage.ellipseShader->SetUniformMat4f("u_View", camera->GetViewMatrix());
		s_Storage.ellipseShader->SetUniformMat4f("u_Proj", camera->GetProjectionMatrix());
	}

	void Renderer2D::DrawQuad(float x, float y, float width, float height, const Vec3& color)
	{
		drawQuad(x, y, width, height, color);
	}

	void Renderer2D::DrawQuad(const Vec2& vertex1, const Vec2& vertex2, const Vec2& vertex3,
	    const Vec2& vertex4, const Vec3& color)
	{
		drawQuad(vertex1, vertex2, vertex3, vertex4, color);
	}

	void Renderer2D::DrawLine(Vec2 start, Vec2 end, float thickness, Vec3 color)
	{
		Vec2 vertex1 = start + (end - start).Perpendicular().Normalize() * thickness;
		Vec2 vertex2 = end + (end - start).Perpendicular().Normalize() * thickness;
		Vec2 vertex3 = end - (end - start).Perpendicular().Normalize() * thickness;
		Vec2 vertex4 = start - (end - start).Perpendicular().Normalize() * thickness;

		drawLine(vertex1, vertex2, vertex3, vertex4, color);
	}

	void Renderer2D::DrawEllipse(Vec2 center, float radiusX, float radiusY, Vec3 color)
	{
		drawEllipse(center, radiusX, radiusY, color);
	}

	void Renderer2D::DrawCircle(Vec2 center, float radius, Vec3 color)
	{
		drawEllipse(center, radius, radius, color);
	}

	// Todo: The order doesn't matter
	void Renderer2D::EndScene()
	{
		if (!s_Storage.quadVertices.empty())
		{
			VertexBuffer vb(s_Storage.quadVertices);
			IndexBuffer ib(s_Storage.quadIndices);

			VertexBufferLayout layout;
			layout.AddFloat(3);
			layout.AddFloat(2);
			layout.AddFloat(3);
			layout.AddFloat(3);

			s_Storage.vao->AddVertexBuffer(vb, layout);
			s_Storage.vao->AddIndexBuffer(ib);

			// Draw call
			s_Storage.quadShader->Bind();
			Renderer::Draw(s_Storage.vao, ib.GetCount());

			s_Storage.quadVertices.clear();
			s_Storage.quadIndices.clear();
		}

		if (!s_Storage.ellipseVertices.empty())
		{
			VertexBuffer vb(s_Storage.ellipseVertices);
			IndexBuffer ib(s_Storage.ellipseIndices);

			VertexBufferLayout layout;
			layout.AddFloat(3);
			layout.AddFloat(2);
			layout.AddFloat(3);
			layout.AddFloat(3);

			s_Storage.vao->AddVertexBuffer(vb, layout);
			s_Storage.vao->AddIndexBuffer(ib);

			// Draw call
			s_Storage.ellipseShader->Bind();
			Renderer::Draw(s_Storage.vao, ib.GetCount());

			s_Storage.ellipseVertices.clear();
			s_Storage.ellipseIndices.clear();
		}

		if (!s_Storage.lineVertices.empty())
		{
			VertexBuffer vb(s_Storage.lineVertices);
			IndexBuffer ib(s_Storage.lineIndices);

			VertexBufferLayout layout;
			layout.AddFloat(3);
			layout.AddFloat(2);
			layout.AddFloat(3);
			layout.AddFloat(3);

			s_Storage.vao->AddVertexBuffer(vb, layout);
			s_Storage.vao->AddIndexBuffer(ib);

			// Draw Call
			s_Storage.lineShader->Bind();
			Renderer::Draw(s_Storage.vao, ib.GetCount());

			s_Storage.lineVertices.clear();
			s_Storage.lineIndices.clear();
		}
	}

	// All private implementations
	void Renderer2D::drawQuad(float x, float y, float width, float height, const Vec3& color)
	{
		drawQuad(Vec2(x - width / 2, y - height / 2), Vec2(x - width / 2, y + height / 2),
		    Vec2(x + width / 2, y + height / 2), Vec2(x + width / 2, y - height / 2), color);
	}

	// Winding order is clockwise
	void Renderer2D::drawQuad(Vec2 vertex1, Vec2 vertex2, Vec2 vertex3, Vec2 vertex4, Vec3 color)
	{
		Vertex quadVert1 = { { vertex1.x, vertex1.y, -20.0f }, { 0.0f, 0.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex quadVert2 = { { vertex2.x, vertex2.y, -20.0f }, { 1.0f, 0.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex quadVert3 = { { vertex3.x, vertex3.y, -20.0f }, { 1.0f, 1.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex quadVert4 = { { vertex4.x, vertex4.y, -20.0f }, { 0.0f, 1.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };

		Vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		// Indices
		s_Storage.quadIndices.push_back(s_Storage.quadVertices.size()); // 0
		s_Storage.quadIndices.push_back(s_Storage.quadVertices.size() + 1); // 1
		s_Storage.quadIndices.push_back(s_Storage.quadVertices.size() + 2); // 2
		s_Storage.quadIndices.push_back(s_Storage.quadVertices.size() + 2); // 2
		s_Storage.quadIndices.push_back(s_Storage.quadVertices.size() + 3); // 3
		s_Storage.quadIndices.push_back(s_Storage.quadVertices.size()); // 0

		// Vertices
		s_Storage.quadVertices.push_back(quadVert1);
		s_Storage.quadVertices.push_back(quadVert2);
		s_Storage.quadVertices.push_back(quadVert3);
		s_Storage.quadVertices.push_back(quadVert4);
	}

	void Renderer2D::drawEllipse(Vec2 center, float radiusX, float radiusY, Vec3 color)
	{
		Vertex vertex1 = { { center.x - radiusX, center.y - radiusY, -20.0f }, { 0.0f, 0.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex vertex2 = { { center.x + radiusX, center.y - radiusY, -20.0f }, { 1.0f, 0.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex vertex3 = { { center.x + radiusX, center.y + radiusY, -20.0f }, { 1.0f, 1.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex vertex4 = { { center.x - radiusX, center.y + radiusY, -20.0f }, { 0.0f, 1.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };

		Vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		// Indices
		s_Storage.ellipseIndices.push_back(s_Storage.ellipseVertices.size()); // 0
		s_Storage.ellipseIndices.push_back(s_Storage.ellipseVertices.size() + 1); // 1
		s_Storage.ellipseIndices.push_back(s_Storage.ellipseVertices.size() + 2); // 2
		s_Storage.ellipseIndices.push_back(s_Storage.ellipseVertices.size() + 2); // 2
		s_Storage.ellipseIndices.push_back(s_Storage.ellipseVertices.size() + 3); // 3
		s_Storage.ellipseIndices.push_back(s_Storage.ellipseVertices.size()); // 0

		// Vertices
		s_Storage.ellipseVertices.push_back(vertex1);
		s_Storage.ellipseVertices.push_back(vertex2);
		s_Storage.ellipseVertices.push_back(vertex3);
		s_Storage.ellipseVertices.push_back(vertex4);
	}

	void Renderer2D::drawLine(Vec2 vertex1, Vec2 vertex2, Vec2 vertex3, Vec2 vertex4, Vec3 color)
	{
		Vertex lineVert1 = { { vertex1.x, vertex1.y, -20.0f }, { 0.0f, 0.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex lineVert2 = { { vertex2.x, vertex2.y, -20.0f }, { 1.0f, 0.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex lineVert3 = { { vertex3.x, vertex3.y, -20.0f }, { 1.0f, 1.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };
		Vertex lineVert4 = { { vertex4.x, vertex4.y, -20.0f }, { 0.0f, 1.0f },
			{ color.x, color.y, color.z }, { 1.0f, 1.0f, 1.0f } };

		Vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		// Indices
		s_Storage.lineIndices.push_back(s_Storage.lineVertices.size()); // 0
		s_Storage.lineIndices.push_back(s_Storage.lineVertices.size() + 1); // 1
		s_Storage.lineIndices.push_back(s_Storage.lineVertices.size() + 2); // 2
		s_Storage.lineIndices.push_back(s_Storage.lineVertices.size() + 2); // 2
		s_Storage.lineIndices.push_back(s_Storage.lineVertices.size() + 3); // 3
		s_Storage.lineIndices.push_back(s_Storage.lineVertices.size()); // 0

		// Vertices
		s_Storage.lineVertices.push_back(lineVert1);
		s_Storage.lineVertices.push_back(lineVert2);
		s_Storage.lineVertices.push_back(lineVert3);
		s_Storage.lineVertices.push_back(lineVert4);
	}

}
