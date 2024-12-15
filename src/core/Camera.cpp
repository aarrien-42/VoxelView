#include "Camera.hpp"

Camera::Camera() {
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

	*this = Camera(position, up, front);
}

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front)
	: m_window(nullptr), m_position(position), m_worldUp(up), m_front(front)
{
	m_yaw = YAW;
	m_pitch = PITCH;
	m_speed = SPEED;
	m_sensitivity = SENSITIVITY;
	m_fov = FOV;

	m_lastX = (float)WINDOW_WIDTH / 2;
	m_lastY = (float)WINDOW_HEIGHT / 2;
	
	UpdateCameraVectors();
}

Camera::~Camera() {}

void Camera::SetWindow(Window* window)
{
	m_window = window;
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
	float deltaTime = m_window->GetDeltaTime();
	if (m_window->GetKeyState(FORWARD) == GLFW_PRESS) {
		m_position += m_front * m_speed * deltaTime;
	}
	if (m_window->GetKeyState(BACKWARD) == GLFW_PRESS) {
		m_position -= m_front * m_speed * deltaTime;
	}
	if (m_window->GetKeyState(RIGHT) == GLFW_PRESS) {
		m_position += m_right * m_speed * deltaTime;
	}
	if (m_window->GetKeyState(LEFT) == GLFW_PRESS) {
		m_position -= m_right * m_speed * deltaTime;
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
	glfwGetCursorPos(m_window->GetWindow(), &currentX, &currentY);
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
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}