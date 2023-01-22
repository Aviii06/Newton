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
		NewtonRenderer::Renderer2D::BeginScene();

		// Draw using API
		NewtonRenderer::Renderer2D::DrawQuad();

		// Update App
		app->GetWindow().Update();
	}

	app->Terminate();
	return 0;
}