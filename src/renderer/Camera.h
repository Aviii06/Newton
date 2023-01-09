#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

struct CameraMovement
{
	enum class Type
	{
		FORWARD = 1,
		BACKWARD = 2,
		LEFT = 3,
		RIGHT = 4
	};
};

class Camera
{
private:
	float m_FOV = 60.0f;
	float m_NearCip = 0.1f;
	float m_FarClip = 500.0f;
	float m_AspectRatio = 1.7778f; // 16:9 = m_ViewportWidth / m_ViewportHeight

	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);

	int m_ViewportWidth = 1280;
	int m_ViewportHeight = 720;

	glm::mat4 m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearCip, m_FarClip);
	glm::mat4 m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, glm::vec3(0.0f, 1.0f, 0.0f));

	// We'll never roll the camera. https://sidvind.com/wiki/Yaw,_pitch,_roll_camera
	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;

	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

	glm::vec2 m_MousePosition = glm::vec2(0.0f, 0.0f);

	void updateCameraVectors();
	void updateProjectionMatrix();
	void updateViewMatrix();

public:
	Camera() = default;

	Camera(float fov, float aspect, float near, float far);

	void ProcessKeyboard(CameraMovement direction, float deltaTime);

	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

	void ProcessMouseScroll(float scrollOffset);

	glm::vec3 GetPosition() { return m_Position; }
	glm::mat4 GetViewMatrix() { return m_ViewMatrix; };
	glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; };
	float GetYaw() { return m_Yaw; }
	float GetPitch() { return m_Pitch; }
	float GetMovementSpeed() { return m_MovementSpeed; }
	float GetMouseSensitivity() { return m_MouseSensitivity; }
	float GetZoom() { return m_Zoom; }
};
