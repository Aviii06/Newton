#include "Renderer2D.h"

namespace NewtonRenderer
{

	Storage Renderer2D::s_Storage;
	void Renderer2D::Init()
	{
		s_Storage.shader = MakeRef<Shader>("./../assets/shaders/basic.vertexShader.hlsl", "./../assets/shaders/basic.pixelShader.hlsl");
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
		s_Storage.mesh = new Mesh(verts, indices);
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene()
	{
		Camera* camera = Camera::GetInstance();

		s_Storage.shader->Bind();
		s_Storage.shader->SetUniformMat4f("u_View", camera->GetViewMatrix());
		s_Storage.shader->SetUniformMat4f("u_Proj", camera->GetProjectionMatrix());
	}

	void Renderer2D::DrawQuad()
	{
		s_Storage.mesh->BindShader(s_Storage.shader);
		s_Storage.mesh->Draw();
	}
}
