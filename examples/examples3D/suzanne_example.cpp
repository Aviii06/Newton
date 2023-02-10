#include "Vivid.h"

int main(void)
{
	Application* app = Application::GetInstance(1920, 1080, "Suzanne Example");

	// Can write custom opengl confs here
	OPENGL_CONFS

	// Light Info
	Vec3 lightColor = Vec3(1.0f, 0.5f, 1.0f);
	Vec3 lightPos = Vec3(0.0f, 0.0f, -100.0f);
	Vivid::Quad3d cube(10.0f, lightColor);
	Vivid::Mesh lightMesh(cube);
	Vivid::PointLight light(lightPos, lightColor, &lightMesh);
	Ref<Vivid::Shader> lightShader = MakeRef<Vivid::Shader>("./../assets/shaders/basic.vertexShader.glsl",
	    "./../assets/shaders/basic.pixelShader.glsl");
	light.Draw(lightShader);

	// Creating a shader
	Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
	    "./../assets/shaders/phong.pixelShader.glsl");

	// Drawing other meshes
	Vivid::Mesh mesh1("./../assets/obj/suzanne.obj");
	mesh1.BindShader(shader);

	glm::vec3 translationModel1(0, 50, -200);

	mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
	mesh1.Draw();

	while (app->IsRunning())
	{
		shader->Bind();
		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPos);
		shader->SetUniform1f("intensity", 2.0f);
		mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
		mesh1.Draw();

		light.UpdateLightPosition(lightPos);
		light.Draw(lightShader);

		app->GetWindow().Update();
	}

	app->Terminate();
	return 0;
}

Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "suzanne");
	return app;
}