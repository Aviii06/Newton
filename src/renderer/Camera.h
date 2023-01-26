#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace Vivid
{
	enum class CameraMovement
	{
		FORWARD = 1,
		BACKWARD = 2,
		LEFT = 3,
		RIGHT = 4
	};

	class Camera
	{
	private:
		static Camera* s_Instance;
		float m_FOV = 60.0f;
		float m_NearCip = 0.1f;
		float m_FarClip = 5000.0f;
		float m_AspectRatio = 1.7778f; // 16:9 = m_ViewportWidth / m_ViewportHeight

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);

		int m_ViewportWidth = 1280;
		int m_ViewportHeight = 720;

		glm::mat4 m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV),
		    m_AspectRatio, m_NearCip, m_FarClip);
		glm::mat4 m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front,
		    glm::vec3(0.0f, 1.0f, 0.0f));

		// We'll never roll the camera. https://sidvind.com/wiki/Yaw,_pitch,_roll_camera
		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;

		float m_MovementSpeed = 2.5f;
		float m_MouseSensitivity = 0.08f;
		float m_ZoomSensitivity = 0.08f;

		glm::vec2 m_MousePosition = glm::vec2(0.0f, 0.0f);

		void updateCameraVectors();
		void updateProjectionMatrix();
		void updateViewMatrix();

		Camera() = default;

		Camera(float fov, float aspect, float near, float far);

	public:
		void ProcessKeyboard(CameraMovement direction);

		void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

		void ProcessMouseScroll(float scrollOffset);

		glm::vec3 GetPosition() { return m_Position; }
		glm::mat4 GetViewMatrix() { return m_ViewMatrix; };
		glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; };
		float GetYaw() { return m_Yaw; }
		float GetPitch() { return m_Pitch; }
		float GetMovementSpeed() { return m_MovementSpeed; }
		float GetMouseSensitivity() { return m_MouseSensitivity; }
		float GetZoom() { return m_ZoomSensitivity; }

		static Camera* GetInstance()
		{
			if (s_Instance == nullptr)
				s_Instance = new Camera(60.0f, 1.7778f, 0.1f, 5000.0f);

			return s_Instance;
		}

		void SetPerspective(glm::mat4 perspective);
		void SetPerspective(float fov, float aspect, float near, float far);

		void SetViewportSize(int width, int height);
		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
	};
}
