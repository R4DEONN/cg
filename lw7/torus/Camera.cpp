#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: m_position(position), m_worldUp(up), m_yaw(yaw), m_pitch(pitch)
{
	updateCameraVectors();
}

void Camera::ProcessMouse(float xoffset, float yoffset)
{
	m_yaw += xoffset * 0.1f;
	m_pitch -= yoffset * 0.1f;

	if (m_pitch > 89.0f) m_pitch = 89.0f;
	if (m_pitch < -89.0f) m_pitch = -89.0f;

	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = 2.0f * deltaTime;

	if (direction == CameraMovement::FORWARD)
		m_position += m_front * velocity;
	if (direction == CameraMovement::BACKWARD)
		m_position -= m_front * velocity;
	if (direction == CameraMovement::LEFT)
		m_position -= m_right * velocity;
	if (direction == CameraMovement::RIGHT)
		m_position += m_right * velocity;
	if (direction == CameraMovement::UP)
		m_position += m_up * velocity;
	if (direction == CameraMovement::DOWN)
		m_position -= m_up * velocity;
}