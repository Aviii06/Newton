#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/shapes/Shape.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/Camera.h"
#include "renderer/PointLight.h"
#include "renderer/shapes/Quad3d.h"
#include "renderer/Window.h"

#include "confs/Config.h"

#include "glm/gtc/matrix_transform.hpp"
#include "utils/timer.h"
#include <glm/glm.hpp>

Camera* Camera::s_Instance;
Renderer* Renderer::s_Instance;
Camera* camera = Camera::GetInstance();
Renderer* renderer = Renderer::GetInstance();

void HandleInput(GLFWwindow* window, Vec2* mousePointer);

int main(void)
{
	Window window(1920, 1080, "Newton");

	OPENGL_CONFS

	// Light Info
	Vec3 lightColor = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 lightPos = Vec3(0.0f, 0.0f, 400.0f);
	Quad3d cube(10.0f, lightColor);
	Mesh lightMesh(cube);
	PointLight light(lightPos, lightColor, &lightMesh);
	Shader* lightShader = new Shader("./../assets/shaders/basic.vertexShader.hlsl", "./../assets/shaders/basic.pixelShader.hlsl");
	light.Draw(lightShader);

	// Creating a shader
	Shader* shader = new Shader("./../assets/shaders/phong.vertexShader.hlsl", "./../assets/shaders/phong.pixelShader.hlsl");

	// Drawing other meshes
	Mesh mesh1("./../assets/obj/suzanne.obj", shader);
	glm::vec3 translationModel1(0, 50, -400);
	mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
	mesh1.Draw();

	// Cursor
	Vec2* mousePointer = new Vec2(0.0f, 0.0f);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		/* Render here */
		renderer->Clear();

		shader->Bind();
		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPos);
		mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
		mesh1.Draw();

		light.UpdateLightPosition(lightPos);
		light.Draw(lightShader);

		/* Poll for and process events */

		// Handle keyboard input
		HandleInput(window.GetWindow(), mousePointer);

		window.Update();
	}

	glfwTerminate();
	return 0;
}

void HandleInput(GLFWwindow* window, Vec2* mousePointer)
{
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::FORWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::BACKWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::LEFT);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::RIGHT);
	}

	// Handle mouse input
	double mouseXPos, mouseYPos;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
		camera->ProcessMouseMovement(mouseXPos - mousePointer->x, mouseYPos - mousePointer->y);
		mousePointer->x = mouseXPos;
		mousePointer->y = mouseYPos;
	}
	else
	{
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
		mousePointer->x = mouseXPos;
		mousePointer->y = mouseYPos;
	}
}