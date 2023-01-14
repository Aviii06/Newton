#include "Window.h"
#include "Camera.h"
#include <iostream>

Window::Window(int width, int height, const char* title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;

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
}
Window::~Window()
{
}
void Window::Clear() const
{
}
void Window::Update()
{
	// Handle keyboard input
//	HandleInput(m_Window, camera, timer.getTimeMs() - time, mousePointer);

	glfwMakeContextCurrent(m_Window);
}