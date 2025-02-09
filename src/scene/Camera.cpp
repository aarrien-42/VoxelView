#include "Camera.hpp"

Camera::Camera ()
{
	glm::vec3 position = glm::vec3 (0.0f, 0.0f, 3.0f);
	glm::vec3 up = glm::vec3 (0.0f, 1.0f, 0.0f);
	glm::vec3 front = glm::vec3 (0.0f, 0.0f, -1.0f);

	*this = Camera (position, up, front);
}

Camera::Camera (glm::vec3 position, glm::vec3 up, glm::vec3 front)
	: m_position (position), m_worldUp (up), m_front (front)
{
	m_yaw = YAW;
	m_pitch = PITCH;
	m_speed = SPEED;
	m_sensitivity = SENSITIVITY;
	m_fov = FOV;

	m_lastX = (float)WINDOW_WIDTH / 2;
	m_lastY = (float)WINDOW_HEIGHT / 2;

	m_invertedX = false;
	m_invertedY = false;

	UpdateCameraVectors ();
}

void Camera::SetPosition (float x, float y, float z)
{
	m_position = glm::vec3 (x, y, z);
}

void Camera::SetRotation (float x, float y, float z)
{
	m_yaw = x;
	m_pitch = y;

	UpdateCameraVectors ();
}

void Camera::HandleKeyboardInput (Action action, float deltaTime)
{
	switch (action)
	{
		case Action::FORWARD: {
			m_position += m_front * m_speed * deltaTime;
			break;
		}
		case Action::BACKWARD: {
			m_position -= m_front * m_speed * deltaTime;
			break;
		}
		case Action::RIGHT: {
			m_position += m_right * m_speed * deltaTime;
			break;
		}
		case Action::LEFT: {
			m_position -= m_right * m_speed * deltaTime;
			break;
		}
		case Action::UP: {
			m_position += m_up * m_speed * deltaTime;
			break;
		}
		case Action::DOWN: {
			m_position -= m_up * m_speed * deltaTime;
			break;
		}
	}
}

void Camera::HandleMouseInput (double& currentX, double& currentY)
{
	static bool firstMouse = true;
	if (firstMouse)
	{
		m_lastX = currentX;
		m_lastY = currentY;
		firstMouse = false;
	}

	float offsetX = (currentX - m_lastX) * m_sensitivity;
	float offsetY = (m_lastY - currentY) * m_sensitivity; // Reversed since y-coordinates range from bottom to top

	if (m_invertedX)
	{
		offsetX = -offsetX;
	}
	if (m_invertedY)
	{
		offsetY = -offsetY;
	}

	m_yaw += offsetX;
	m_pitch += offsetY;

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}
	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}

	m_lastX = currentX;
	m_lastY = currentY;

	UpdateCameraVectors ();
}

void Camera::Move (float x, float y, float z)
{
	m_position = glm::vec3 (x, y, z);
}

void Camera::Rotate (float x, float y, float z)
{
	m_yaw = x;
	m_pitch = y;

	UpdateCameraVectors ();
}

void Camera::Zoom (float x)
{
	m_fov = x;
}

glm::mat4 Camera::GetViewMatrix () const
{
	return glm::lookAt (m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetPerspectiveProjectionMatrix () const
{
	return glm::perspective (glm::radians (m_fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
}

glm::mat4 Camera::GetOrthogonalProjectionMatrix () const
{
	return glm::ortho (0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f);
}

void Camera::UpdateCameraVectors ()
{
	m_front.x = cos (glm::radians (m_yaw)) * cos (glm::radians (m_pitch));
	m_front.y = sin (glm::radians (m_pitch));
	m_front.z = sin (glm::radians (m_yaw)) * cos (glm::radians (m_pitch));
	m_front = glm::normalize (m_front);

	m_right = glm::normalize (glm::cross (m_front, m_worldUp));
	m_up = glm::normalize (glm::cross (m_right, m_front));
}