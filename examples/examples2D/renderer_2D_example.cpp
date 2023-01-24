#include "NewtonRenderer.h"

int main(void)
{
	Application* app = Application::GetInstance(1920, 1080, "Renderer2D Example");

	// Can write custom opengl confs here
	OPENGL_CONFS

	// Intiialize 2D rendering Context
	NewtonRenderer::Renderer2D::Init();
	while (app->IsRunning())
	{
		// Begin Scene
		// Todo: Fix order. Currently first draw call is render and is never overwritten.
		NewtonRenderer::Renderer2D::BeginScene();

		// Draw using API
		NewtonRenderer::Renderer2D::DrawCircle(Vec2(0, 0), 200, Vec3(0.0f, 1.0f, 0.0f));

//		NewtonRenderer::Renderer2D::DrawLine(Vec2(-150, 100), Vec2(150, 150),2,Vec3(1.0f, 0.5f, 0.0f));

//		NewtonRenderer::Renderer2D::DrawQuad(-250, -150, 100, 100, Vec3(1.0f, 1.0f, 0.0f));

		NewtonRenderer::Renderer2D::EndScene();
		// Update App
		app->GetWindow().Update();
	}

	app->Terminate();
	return 0;
}