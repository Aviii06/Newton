#pragma once
#include "../common/types.h"
#include "Window.h"

class Application
{
private:
	static Application* s_Instance;
	int m_Width = 1920, m_Height = 1080;
	const char* m_Title = "Newton";
	Application();
	Application(int width, int height, const char* title);
	Ptr<Window> m_Window;
	bool m_Running = true;

public:
	void Run();
	static Application* GetInstance()
	{
		if (s_Instance == nullptr)
			s_Instance = new Application();
		return s_Instance;
	}
	Window& GetWindow() { return *m_Window; }
};