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

#include "glm/gtc/matrix_transform.hpp"
#include "utils/timer.h"
#include <glm/glm.hpp>

#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui/imgui.h"

Camera* Camera::s_Instance;
Renderer* Renderer::s_Instance;
Camera* camera = Camera::GetInstance();
Renderer* renderer = Renderer::GetInstance();

void HandleInput(GLFWwindow* window, Camera* camera, float deltaTime, Vec2* mousePointer);

int main(void)
{
	Window window(1920, 1080, "Newton");

	glEnable(GL_DEPTH_TEST);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "F";
	}

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	// GLCall( glEnable(GL_CULL_FACE) );

	// Create a camera

	VertexBufferLayout layout;
	layout.AddFloat(3); // Positions
	layout.AddFloat(2); // Tex coords
	layout.AddFloat(3); // Colors
	layout.AddFloat(3); // Normal

	// Light Info
	Vec3 lightColor = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 lightPos = Vec3(0.0f, 0.0f, 400.0f);
	Quad3d cube(10.0f, lightColor);
	Mesh lightMesh(cube);
	PointLight light(lightPos, lightColor, &lightMesh);
	Shader lightShader("./../assets/shaders/basic.vertexShader.hlsl", "./../assets/shaders/basic.pixelShader.hlsl");
	lightShader.Bind();
	light.Draw(lightShader);

	// Creating a shader
	Shader shader("./../assets/shaders/phong.vertexShader.hlsl", "./../assets/shaders/phong.pixelShader.hlsl");
	shader.Bind();

	// Creating a texture
	Texture texture("./../assets/textures/mandelbrot.png");
	texture.Bind();

	// Drawing other meshes
	Mesh mesh1("./../assets/obj/suzanne.obj");
	glm::vec3 translationModel1(0, 50, -400);
	mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
	mesh1.Draw(shader);

	// Timer
	Timer timer;
	float time = timer.getTimeMs();

	// Cursor
	Vec2* mousePointer = new Vec2(0.0f, 0.0f);

	// IMGUI Setup

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	double xPosPrev, yPosPrev;

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		/* Render here */
		renderer->Clear();

		shader.Bind();
		shader.SetUniform4f("u_Color", 0.1, 0.3, 0.8, 1.0);

		shader.SetUniform3f("lightColor", lightColor);
		shader.SetUniform3f("lightPos", lightPos);

		mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
		mesh1.Draw(shader);

		light.UpdateLightPosition(lightPos);
		light.Draw(lightShader);

		/* Poll for and process events */

		// Handle keyboard input
		HandleInput(window.GetWindow(), camera, timer.getTimeMs() - time, mousePointer);

		time = timer.getTimeMs();

		// IMGUI
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug");
		ImGui::SliderFloat3("Translation Model 1", &translationModel1.x, -500.0f, 500.0f);
		// ImGui::SliderFloat3("Translation Model 2", &translationModel2.x, -300.0f, 300.0f);
		ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window.GetWindow());

		/* Poll for and process events */

		glClear(GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}

	glfwTerminate();
	return 0;
}

void HandleInput(GLFWwindow* window, Camera* camera, float deltaTime, Vec2* mousePointer)
{
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
	}

	// Handle mouse input
	double mouseXPos, mouseYPos;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
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