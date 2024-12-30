#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/input/IControl.hpp"
#include "core/window/Window.hpp"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 90.0f;

class Camera : public IControl {
	public:
		Camera ();
		Camera (glm::vec3 position, glm::vec3 up, glm::vec3 front);
		~Camera () = default;

		void SetPosition (float x, float y, float z);
		void SetRotation (float x, float y, float z);

		glm::vec3 GetPosition () const { return m_position; }

		void HandleKeyboardInput (Action action, float deltaTime) override;
		void HandleMouseInput (double& x, double& y) override;

		void Move (float x, float y, float z);
		void Rotate (float x, float y, float z);
		void Zoom (float x);

		glm::mat4 GetViewMatrix () const;
		glm::mat4 GetProjectionMatrix () const;
	private:
		void UpdateCameraVectors ();
	private:
		bool m_invertedX;
		bool m_invertedY;

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