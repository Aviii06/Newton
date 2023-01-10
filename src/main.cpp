#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/Shapes/Shape.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/Camera.h"
#include "renderer/PointLight.h"
#include "renderer/Shapes/Quad3d.h"

#include "glm/gtc/matrix_transform.hpp"
#include "utils/timer.h"
#include <glm/glm.hpp>

#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui/imgui.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		return -1;
	}

	// FOR MACOS
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	int Width = 1280, Height = 720;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Width, Height, "Newton", NULL, NULL);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glEnable(GL_DEPTH_TEST);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "F";
	}

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	// GLCall( glEnable(GL_CULL_FACE) );

	// Create a camera
	float field_of_view = 60.0f;
	float closestDistance = 0.1f;
	float farthestDistance = 500.0f;

	Camera camera(field_of_view, (float)Width / Height, closestDistance, farthestDistance);

	VertexBufferLayout layout;
	layout.AddFloat(3); // Positions
	layout.AddFloat(2); // Tex coords
	layout.AddFloat(3); // Colors
	layout.AddFloat(3); // Normal

	// Creating a renderer
	Renderer renderer;

	// Light Info
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, -400.0f);
	Quad3d cube(10.0f, lightColor);
	PointLight light(lightPos, lightColor, cube);
	Shader lightShader("./../assets/shaders/basic.vertexShader.hlsl", "./../assets/shaders/basic.pixelShader.hlsl");
	lightShader.Bind();
	light.Draw(lightShader, renderer, camera);


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
	mesh1.Draw(shader, renderer, camera);

	Mesh mesh2("./../assets/obj/plane.obj");
	glm::vec3 translationModel2(0, 100, -400);
	mesh2.Update(glm::translate(glm::mat4(1.0f), translationModel2));
	// mesh2.Draw(shader, renderer, camera);

	// Timer
	Timer timer;
	float time = timer.getTimeMs();

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
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		shader.Bind();
		shader.SetUniform4f("u_Color", 0.1, 0.3, 0.8, 1.0);

		shader.SetUniform3f("lightColor", lightColor);
		shader.SetUniform3f("lightPos", lightPos);

		mesh1.Update(glm::translate(glm::mat4(1.0f), translationModel1));
		mesh1.Draw(shader, renderer, camera);

		mesh2.Update(glm::translate(glm::mat4(1.0f), translationModel2));
		// mesh2.Draw(shader, renderer, camera);

		light.UpdateLightPosition(lightPos);
		light.Draw(lightShader, renderer, camera);

		// IMGUI
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug");
		ImGui::SliderFloat3("Translation Model 1", &translationModel1.x, -500.0f, 500.0f);
		ImGui::SliderFloat3("Translation Model 2", &translationModel2.x, -300.0f, 300.0f);
		ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);
		ImGui::SliderFloat("Field of View", &field_of_view, 15.0f, 90.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */

		glfwPollEvents();
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	glfwTerminate();
	return 0;
}