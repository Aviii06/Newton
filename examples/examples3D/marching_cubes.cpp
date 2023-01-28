#include "Vivid.h"

int main()
{
	Application* app = Application::GetInstance(1920, 1080, "Marching Cubes");

	OPENGL_CONFS

	Vivid::Renderer3D::Init();

	while (app->IsRunning())
	{
		Vivid::Renderer3D::BeginScene();

		Vivid::Renderer3D::DrawQuad(
		    Vec3(0, 0, 0),
		    Vec3(100, 0, 0),
		    Vec3(100, 100, 0),
		    Vec3(0, 100, 0),
		    Vec3(1.0f, 1.0f, 0.0f));

		Vivid::Renderer3D::EndScene();
		app->GetWindow().Update();
	}

	return 0;
}