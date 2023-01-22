#pragma once

#include "common/Types.h"
#include "utils/Error.h"

class Window
{
private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
	const char* m_Title;
	Vec2* m_PrevMousePosition;

public:
	Window(int width, int height, const char* title);

	~Window() = default;
	static Ptr<Window> Init(int width, int height, const char* title);
	void Clear() const;
	void Update();

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	GLFWwindow* GetGLFWWindow() const { return m_Window; }
	float GetAspectRatio() const { return (float)m_Width / (float)m_Height; }
};