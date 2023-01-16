#include "Window.h"
#include "Camera.h"
#include <iostream>
#include "../confs/Config.h"
#include "../inputs/InputHandler.h"

#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui/imgui.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/error.h"

Window::Window(int width, int height, const char* title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;
	m_PrevMousePosition = new Vec2(0.0f, 0.0f);

	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize!" << std::endl;
	}

	// FOR MACOS
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, 1);
	if (!m_Window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);

	IMGUI_CONFS

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
}

Window::~Window()
{
}

void Window::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	// Handle keyboard input
	//	HandleInput(m_Window, camera, timer.getTimeMs() - time, mousePointer);
	glfwPollEvents();

	Camera* camera = Camera::GetInstance();
	glfwPollEvents();
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::FORWARD);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::BACKWARD);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::LEFT);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(CameraMovement::RIGHT);
	}

	// Handle mouse input
	double mouseXPos, mouseYPos;
	Vec2* mousePointer = new Vec2();
	if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwGetCursorPos(m_Window, &mouseXPos, &mouseYPos);
		camera->ProcessMouseMovement(mouseXPos - m_PrevMousePosition->x, mouseYPos - m_PrevMousePosition->y);
		camera->ProcessMouseMovement(mouseXPos - m_PrevMousePosition->x, mouseYPos - m_PrevMousePosition->y);
		m_PrevMousePosition->x = mouseXPos;
		m_PrevMousePosition->x = mouseYPos;
	}
	else
	{
		glfwGetCursorPos(m_Window, &mouseXPos, &mouseYPos);
		m_PrevMousePosition->x = mouseXPos;
		m_PrevMousePosition->y = mouseYPos;
	}

	// IMGUI
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Debug");
	//	ImGui::SliderFloat3("Translation Model 1", &translationModel1.x, -500.0f, 500.0f);
	//	// ImGui::SliderFloat3("Translation Model 2", &translationModel2.x, -300.0f, 300.0f);
	//	ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
	    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwMakeContextCurrent(m_Window);
	glfwSwapBuffers(m_Window);

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}