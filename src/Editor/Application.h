#pragma once
#include "common/Types.h"
#include "Window.h"
#include <iostream>
#include "confs/DynamicExportingMacros.h"
#include "Editor/RenderingInterface.h"

class VIVAPI Application
{
private:
	static Application* s_Instance;
	int m_Width, m_Height;
	const char* m_Title;
	Application();
	Application(int width, int height, const char* title);

	Ptr<Window> m_Window;

public:
	bool IsRunning();
	void Run();

	// TODO: Fix this semantically
	static Application* GetInstance(int width = 1920, int height = 1080, const char* title = "Newton")
	{
		if (s_Instance == NULL)
			s_Instance = new Application(width, height, title);
		return s_Instance;
	}

	Window& GetWindow() { return *m_Window; }
	void Terminate();

	void SetRenderingInterface(RenderingInterface* renderingInterface) { m_Window->SetRenderingInterface(renderingInterface); }
};

namespace Vivid
{
	Application* CreateApplication();
}