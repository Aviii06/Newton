#include "InputHandler.h"
#include <iostream>
#include "../Editor/Application.h"

bool InputHandler::IsKeyPressed(int key)
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetGLFWWindow();
	int state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

Vec2 InputHandler::GetMousePosition()
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetGLFWWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return Vec2((float)xpos, (float)ypos);
}

bool InputHandler::IsMouseButtonPressed(int button)
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetGLFWWindow();
	int state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}
