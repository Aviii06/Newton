#include "NewtonRenderer.h"

int main(void)
{
	Application* app = Application::GetInstance(1920, 1080, "Marching Squares");

	OPENGL_CONFS

	int dim = 5;

	NewtonRenderer::Renderer2D::Init();

	while(app->IsRunning())
	{
		NewtonRenderer::Renderer2D::BeginScene();

		for (int i = -1920 / (4 * dim); i < 1920 / (4 * dim); i++)
		{
			for (int j = -1080 / (4 * dim) ; j < 1080 / (4 * dim); j++)
			{
//				NewtonRenderer::Renderer2D::DrawCircle(Vec2(2 * i * dim, 2 * j * dim), dim, Vec3(1.0f, 0.0f, 1.0f));
				NewtonRenderer::Renderer2D::DrawLine(Vec2(2 * i * dim, 2 * j * dim), Vec2(2 * (i + 1) * dim, 2 * j * dim), 1.0f, Vec3(1.0f, 0.12f, 0.5f));
				NewtonRenderer::Renderer2D::DrawLine(Vec2(2 * i * dim, 2 * j * dim), Vec2(2 * i * dim, 2 * (j + 1) * dim), 1.0f, Vec3(1.0f, 0.12f, 0.5f));
			}
		}

		NewtonRenderer::Renderer2D::EndScene();

		app->GetWindow().Update();
	}
}