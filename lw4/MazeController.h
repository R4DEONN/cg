#pragma once

#include <GLFW/glfw3.h>
#include "MazeModel.h"

class MazeController
{
public:
	void HandleInput(GLFWwindow* window)
	{
		const float moveSpeed = 0.08f;
		const float rotateSpeed = 0.15f;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_model.MoveCamera(moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_model.MoveCamera(-moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_model.MoveCameraStrafe(-moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_model.MoveCameraStrafe(moveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			m_model.RotateCamera(-rotateSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			m_model.RotateCamera(rotateSpeed);
		}
	}

	[[nodiscard]] const MazeModel& GetModel() const
	{
		return m_model;
	}

private:
	MazeModel m_model;
};
