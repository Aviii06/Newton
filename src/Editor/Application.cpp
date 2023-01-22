#include "Application.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	m_Window = Window::Init(m_Width, m_Height, m_Title);
}

Application::Application(int width, int height, const char* title)
	: m_Width(width), m_Height(height), m_Title(std::move(title))
{
	if (title == nullptr)
		m_Title = "Newton";
	m_Window = Window::Init(m_Width, m_Height, m_Title);
}

bool Application::IsRunning()
{
	return !glfwWindowShouldClose(m_Window->GetGLFWWindow());
}
