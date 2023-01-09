#include "Camera.h"

Camera::Camera(float fov, float aspect, float near, float far)
    : m_FOV(fov)
    , m_AspectRatio(aspect)
    , m_NearCip(near)
    , m_FarClip(far)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearCip, m_FarClip);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
}
void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
}
void Camera::ProcessMouseScroll(float scrollOffset)
{
}
void Camera::updateCameraVectors()
{
}
void Camera::updateProjectionMatrix()
{
}
void Camera::updateViewMatrix()
{
}
