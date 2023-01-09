#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/Shapes.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/Camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "utils/timer.h"
#include <glm/glm.hpp>

#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui/imgui.h"

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void keyCallBack(GLFWwindow* window, int key, int SCANCODE, int action, int mode);

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
	int Width = 640, Height = 400;
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

	// Todo: Do this in using one renderer
	Renderer renderer;
	Renderer renderer2;
	Renderer renderer3;

	Shader shader("./../assets/shaders/basic.vertexShader.hlsl", "./../assets/shaders/basic.pixelShader.hlsl");
	shader.Bind();

	Texture texture("./../assets/textures/mandelbrot.png");
	texture.Bind();

	// Light Info
	// Todo: Make this a class or struct
	float size = 10.0f;
	shape::quad3d q(size);
	Vector<Vertex> verts3 = q.getPositions();
	Vector<unsigned int> inds3 = q.getIndices();
	size_t indSize = q.getIndicesSize();
	size_t posSize = q.getPositionsSize();
	glm::vec4 lightColor(1.0, 1.0, 0.5, 1.0);
	glm::vec3 lightPos(0, 0, -400);
	glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);

	Shader lightShader("./../assets/shaders/basic.vertexShader.hlsl", "./../assets/shaders/basic.pixelShader.hlsl");
	lightShader.Bind();

	Mesh mesh3(verts3, inds3, layout, lightModel);
	mesh3.Update(lightModel);
	mesh3.Draw(lightShader, renderer3, camera);

	// Drawing other meshes
	glm::vec3 translationModel(0, 50, -400); // Default values for optimal viewing
	glm::vec3 translationModel2(0, 100, -400);
	glm::vec3 translationView(0, 0, 0);

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translationModel);
	glm::mat4 modelMatrix2 = glm::translate(glm::mat4(1.0f), translationModel2);
	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), translationView);

	// glm::vec3 translationModel(0, -118.857, -314.019); //Default values for optimal viewing
	// glm::vec3 translationView(-20, -100, 96.262);
	// float viewRotAngle = 43.088;

	float viewRotAngle = 0;
	Mesh mesh("./../assets/obj/plane.obj");
	mesh.Draw(shader, renderer, camera);

	Mesh mesh2("./../assets/obj/plane.obj");
	mesh2.Draw(shader, renderer2, camera);

	Timer timer;
	float time = timer.getTimeMs();

	// Shader
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform1f("u_Time", time);

	float aspect = (float)Width / Height;
	shader.SetUniform1f("u_Aspect", aspect);

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

	// MVP matrix
	glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)Width,
	    0.0f, (float)Height,
	    -1.0f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();
		renderer2.Clear();
		renderer3.Clear();
		glfwSetKeyCallback(window, keyCallBack);

		mesh.Update(glm::translate(glm::mat4(1.0f), translationModel));
		mesh2.Update(glm::translate(glm::mat4(1.0f), translationModel2));
		viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		float rotation = time / 100.0;
		// modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		// modelMatrix2 = glm::rotate(modelMatrix2, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		// viewMatrix = glm::rotate(viewMatrix, glm::radians(viewRotAngle), glm::vec3(1.0f, 0.0f, 0.0f));

		shader.Bind();
		shader.SetUniform4f("u_Color", 0.1, 0.3, 0.8, 1.0);
		time = timer.getTimeMs();

		projectionMatrix = glm::perspective(glm::radians(field_of_view), aspect, closestDistance, farthestDistance);

		shader.SetUniform1f("u_Time", time);
		shader.SetUniform4f("lightColor", lightColor);
		shader.SetUniform3f("lightPos", lightPos);
		mesh.Draw(shader, renderer, camera);

		mesh2.Draw(shader, renderer, camera);

		lightModel = glm::translate(glm::mat4(1.0f), lightPos);
		lightShader.Bind();
		lightShader.SetUniform1f("u_Time", time);
		lightShader.SetUniform4f("lightColor", lightColor);
		lightShader.SetUniform3f("lightPos", lightPos);
		mesh3.Draw(lightShader, renderer3, camera);

		// IMGUI
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug");
		ImGui::SliderFloat3("Translation Model 1", &translationModel.x, -500.0f, 500.0f);
		ImGui::SliderFloat3("Translation Model 2", &translationModel2.x, -300.0f, 300.0f);
		ImGui::SliderFloat3("Translation View", &translationView.x, -300.0f, 300.0f);
		ImGui::SliderFloat3("Light Position", &lightPos.x, -100.0f, 100.0f);
		ImGui::SliderFloat("Angle of Camera", &viewRotAngle, -90.0f, 90.0f);
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