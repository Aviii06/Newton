#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
	const char* m_Title;
public:
	Window(int width, int height, const char* title);
	~Window();
	void Clear() const;
	void Update();

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	GLFWwindow* GetWindow() const { return m_Window; }
	float GetAspectRatio() const { return (float)m_Width / (float)m_Height; }
};