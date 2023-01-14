#include "Camera.h"

Camera::Camera(float fov, float aspect, float near, float far)
    : m_FOV(fov)
    , m_AspectRatio(aspect)
    , m_NearCip(near)
    , m_FarClip(far)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearCip, m_FarClip);
}

// Process keyboard input
void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;

	switch (direction)
	{
	case CameraMovement::FORWARD:
		m_Position += m_Front * velocity;
		break;
	case CameraMovement::BACKWARD:
		m_Position -= m_Front * velocity;
		break;
	case CameraMovement::RIGHT:
		m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
		break;
	case CameraMovement::LEFT:
		m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
		break;
	}

	updateViewMatrix();
}

// Process mouse movement
void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	xOffset *= m_MouseSensitivity;
	yOffset *= m_MouseSensitivity;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	updateCameraVectors();
	updateViewMatrix();
}

// Process mouse scroll
void Camera::ProcessMouseScroll(float scrollOffset)
{
	if (m_ZoomSensitivity >= 1.0f && m_ZoomSensitivity <= 45.0f)
		m_ZoomSensitivity -= scrollOffset;
	if (m_ZoomSensitivity <= 1.0f)
		m_ZoomSensitivity = 1.0f;
	if (m_ZoomSensitivity >= 45.0f)
		m_ZoomSensitivity = 45.0f;

	updateProjectionMatrix();
}

// Update camera vectors
void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = -sin(glm::radians(m_Pitch));
	front.z = -cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f))); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
void Camera::updateProjectionMatrix()
{
}

// Updates view matrix based on camera position and orientation
void Camera::updateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::SetPerspective(float fov, float aspect, float near, float far)
{
	m_FOV = fov;
	m_AspectRatio = aspect;
	m_NearCip = near;
	m_FarClip = far;
	updateProjectionMatrix();
}
