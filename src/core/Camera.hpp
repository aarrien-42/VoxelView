#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/window/Window.hpp"

enum CameraMovement {
	FORWARD = GLFW_KEY_W,
	BACKWARD = GLFW_KEY_S,
	LEFT = GLFW_KEY_A,
	RIGHT = GLFW_KEY_D,
	UP = GLFW_KEY_SPACE,
	DOWN = GLFW_KEY_LEFT_SHIFT,
};

enum CameraMovementProfile{
	FPS, // First Person Shooter
	TPS, // Third Person Shooter
	FLY, // Free Fly
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 90.0f;

class Camera {
	public:
		Camera();
		Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front);
		~Camera();

		void SetWindow(Window* window);
		void SetMovementProfile(CameraMovementProfile profile);
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);

		void ProcessKeyboard();
		void ProcessMouseMove(float currentX, float currentY);
		void ProcessMouseScroll(float y);

		void Update();
		void Move(float x, float y, float z);
		void Rotate(float x, float y, float z);
		void Zoom (float x);

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;
	private:
		void UpdateCameraVectors();
	private:
		CameraMovementProfile m_movementProfile;
		bool m_invertedX;
		bool m_invertedY;
		Window* m_window;

		glm::vec3 m_position;
		glm::vec3 m_worldUp;
		glm::vec3 m_up;
		glm::vec3 m_front;
		glm::vec3 m_right;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		float m_lastX;
		float m_lastY;

		float m_yaw;
		float m_pitch;
		float m_speed;
		float m_sensitivity;
		float m_fov;
};