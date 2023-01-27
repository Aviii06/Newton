#include "Window.h"
#include "renderer/Camera.h"
#include <iostream>
#include "confs/Config.h"
#include "inputs/InputHandler.h"

#include "renderer/Renderer.h"
#include "ui/UI.h"

InputHandler* InputHandler::s_Instance;
Vivid::Camera* Vivid::Camera::s_Instance;

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

//	UI::Init(m_UIUpadateCallback);

	glfwMakeContextCurrent(m_Window);
}

Ptr<Window> Window::Init(int width, int height, const char* title)
{
	return MakePtr<Window>(width, height, title);
}

void Window::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	// Handle keyboard input
	glfwPollEvents();

	Vivid::Camera* camera = Vivid::Camera::GetInstance();
	if (InputHandler::GetInstance()->IsKeyPressed(GLFW_KEY_W))
	{
		camera->MoveForward();
	}
	if (InputHandler::GetInstance()->IsKeyPressed(GLFW_KEY_S))
	{
		camera->MoveBackward();
	}
	if (InputHandler::GetInstance()->IsKeyPressed(GLFW_KEY_A))
	{
		camera->MoveLeft();
	}
	if (InputHandler::GetInstance()->IsKeyPressed(GLFW_KEY_D))
	{
		camera->MoveRight();
	}

	// Handle mouse input
	Vec2 mousePosition = InputHandler::GetInstance()->GetMousePosition();
	if (InputHandler::GetInstance()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		camera->ProcessMouseMovement(mousePosition.x - m_PrevMousePosition->x,
		    mousePosition.y - m_PrevMousePosition->y);
		m_PrevMousePosition->x = mousePosition.x;
		m_PrevMousePosition->y = mousePosition.y;
	}
	else
	{
		m_PrevMousePosition->x = mousePosition.x;
		m_PrevMousePosition->y = mousePosition.y;
	}

	// UI
//	OnUIUpdate();

	glfwMakeContextCurrent(m_Window);
	glfwSwapBuffers(m_Window);

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Vivid::Renderer::Clear();
}