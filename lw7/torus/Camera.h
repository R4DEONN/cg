#pragma once

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>

enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};


class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(2.5f, 1.5f, 2.5f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f,
		float pitch = 0.0f);

	void ProcessMouse(float xoffset, float yoffset);
	void ProcessKeyboard(CameraMovement direction, float deltaTime);

	glm::mat4 GetViewMatrix() const;

	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;

private:
	void updateCameraVectors();
};