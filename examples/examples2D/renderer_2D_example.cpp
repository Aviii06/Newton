#include "Vivid.h"

int main(void)
{
	Application* app = Application::GetInstance(1920, 1080, "Renderer2D Example");

	// Can write custom opengl confs here
	OPENGL_CONFS

	// Intiialize 2D rendering Context
	Vivid::Renderer2D::Init();
	const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
	const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model
//	while (app->IsRunning())
//	{
//		// Begin Scene
//		// Todo: Fix order. Currently quads will always be drawn first
//		Vivid::Renderer2D::BeginScene();
//
//		// Draw using API
//		Vivid::Renderer2D::DrawCircle(Vec2(0, 0), 150, Vec3(0.0f, 1.0f, 0.0f));
//
//		Vivid::Renderer2D::DrawLine(Vec2(-150, 0), Vec2(150, 0), 2,
//		    Vec3(1.0f, 0.5f, 0.0f));
//
//		Vivid::Renderer2D::DrawQuad(-200, -200, 100, 100, Vec3(1.0f, 1.0f, 0.0f));
//
//		Vivid::Renderer2D::EndScene();
//		// Update App
//		app->GetWindow().Update();
//	}
	app->Run();

	app->Terminate();
	return 0;
}