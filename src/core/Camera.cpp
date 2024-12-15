#include "Camera.hpp"

Camera::Camera() {
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

	*this = Camera(position, up, front);
}

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front)
	: m_window(nullptr), m_movementProfile(FPS), m_position(position), m_worldUp(up), m_front(front)
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
	
	UpdateCameraVectors();
}

Camera::~Camera() {}

void Camera::SetWindow(Window* window)
{
	m_window = window;
}

void Camera::SetMovementProfile(CameraMovementProfile profile)
{
	m_movementProfile = profile;
}

void Camera::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void Camera::SetRotation(float x, float y, float z)
{
	m_yaw = x;
	m_pitch = y;

	UpdateCameraVectors();
}

void Camera::ProcessKeyboard()
{
	bool movingForward = (m_window->GetKeyState(FORWARD) == GLFW_PRESS);
	bool movingBackward = (m_window->GetKeyState(BACKWARD) == GLFW_PRESS);
	bool movingRight = (m_window->GetKeyState(RIGHT) == GLFW_PRESS);
	bool movingLeft = (m_window->GetKeyState(LEFT) == GLFW_PRESS);
	bool movingUp = (m_window->GetKeyState(UP) == GLFW_PRESS);
	bool movingDown = (m_window->GetKeyState(DOWN) == GLFW_PRESS);
	
	bool worldRelativeMove;
	if (m_movementProfile == FPS || m_movementProfile == TPS) {
		worldRelativeMove = true;
	} else {
		worldRelativeMove = false;
	}

	float deltaTime = m_window->GetDeltaTime();
	if (movingForward) {
		if (worldRelativeMove) {
			glm::vec3 relFront = glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z));
			m_position += relFront * m_speed * deltaTime;
		} else {
			m_position += m_front * m_speed * deltaTime;
		}
	}
	if (movingBackward) {
		if (worldRelativeMove) {
			glm::vec3 relFront = glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z));
			m_position -= relFront * m_speed * deltaTime;
		} else {
			m_position -= m_front * m_speed * deltaTime;
		}
	}
	if (movingRight) {
		m_position += m_right * m_speed * deltaTime;
	}
	if (movingLeft) {
		m_position -= m_right * m_speed * deltaTime;
	}
	if (movingUp) {
		if (worldRelativeMove) {
			m_position += m_worldUp * m_speed * deltaTime;
		}
		else {
			m_position += m_up * m_speed * deltaTime;
		}
	}
	if (movingDown) {
		if (worldRelativeMove) {
			m_position -= m_worldUp * m_speed * deltaTime;
		} else {
			m_position -= m_up * m_speed * deltaTime;
		}
	}
}

void Camera::ProcessMouseMove(float currentX, float currentY)
{
	static bool firstMouse = true;
	if (firstMouse) {
		m_lastX = currentX;
		m_lastY = currentY;
		firstMouse = false;
	}
	
	float offsetX = (currentX - m_lastX) * m_sensitivity;
	float offsetY = (m_lastY - currentY) * m_sensitivity; // Reversed since y-coordinates range from bottom to top
	
	if (m_invertedX) {
		offsetX = -offsetX;
	}
	if (m_invertedY) {
		offsetY = -offsetY;
	}

	m_yaw += offsetX;
	m_pitch += offsetY;
	
	if (m_pitch > 89.0f) {
		m_pitch = 89.0f;
	}
	if (m_pitch < -89.0f) {
		m_pitch = -89.0f;
	}

	m_lastX = currentX;
	m_lastY = currentY;
	
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float y)
{
	m_fov -= y;
	if (m_fov < 1.0f) {
		m_fov = 1.0f;
	}
	if (m_fov > 45.0f) {
		m_fov = 45.0f;
	}
}

void Camera::Update()
{
	// Mouse input
	double currentX = 0.0, currentY = 0.0;
	m_window->GetCursorPos(currentX, currentY);
	ProcessMouseMove(currentX, currentY);

	// Keyboard input
	ProcessKeyboard();
	UpdateCameraVectors();
	
}

void Camera::Move(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void Camera::Rotate(float x, float y, float z)
{
	m_yaw = x;
	m_pitch = y;

	UpdateCameraVectors();
}

void Camera::Zoom(float x)
{
	m_fov = x;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(m_fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
}

void Camera::UpdateCameraVectors()
{
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}