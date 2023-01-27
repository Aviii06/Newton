#include "Application.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	m_Window = Window::Init(m_Width, m_Height, m_Title);
}

Application::Application(int width, int height, const char* title)
    : m_Width(width)
    , m_Height(height)
    , m_Title(std::move(title))
{
	if (title == nullptr)
		m_Title = "Newton";
	m_Window = Window::Init(m_Width, m_Height, m_Title);
	m_UI = new UI();
	m_UI->Init();
}

bool Application::IsRunning()
{
	return !glfwWindowShouldClose(m_Window->GetGLFWWindow());
}
void Application::Terminate()
{
	glfwTerminate();
}

void Application::Run()
{
	while (IsRunning())
	{
		m_Window->Update();
		m_UI->Update();
	}
}
