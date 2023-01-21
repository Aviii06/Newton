#include "../src/NewtonRenderer.h"

int main(void)
{
	Application* app = Application::GetInstance();

	OPENGL_CONFS

	// Light Info
	Vec3 lightColor = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 lightPos = Vec3(0.0f, 0.0f, 400.0f);
	NewtonRenderer::Quad3d cube(10.0f, lightColor);
	NewtonRenderer::Mesh lightMesh(cube);
	NewtonRenderer::PointLight light(lightPos, lightColor, &lightMesh);
	NewtonRenderer::Shader* lightShader = new NewtonRenderer::Shader("./../assets/shaders/basic.vertexShader.hlsl", "./../assets/shaders/basic.pixelShader.hlsl");
	light.Draw(lightShader);

	// Creating a shader
	NewtonRenderer::Shader* shader = new NewtonRenderer::Shader("./../assets/shaders/phong.vertexShader.hlsl", "./../assets/shaders/phong.pixelShader.hlsl");

	// Drawing other meshes
	NewtonRenderer::Mesh mesh1("./../assets/obj/suzanne.obj", shader);
	glm::vec3 translationModel1(0, 50, -400);
	mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
	mesh1.Draw();

	// Cursor

	while (!glfwWindowShouldClose(app->GetWindow().GetGLFWWindow()))
	{
		/* Render here */
		NewtonRenderer::Renderer::GetInstance()->Clear();

		shader->Bind();
		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPos);
		mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
		mesh1.Draw();

		light.UpdateLightPosition(lightPos);
		light.Draw(lightShader);

		app->GetWindow().Update();
	}

	glfwTerminate();
	return 0;
}