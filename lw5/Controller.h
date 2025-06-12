//
// Created by admin on 04.04.2025.
//

#pragma once

#include <GLFW/glfw3.h>

#include <utility>
#include "View.h"

class Controller
{
private:
	std::shared_ptr<Model> m_model;
	std::shared_ptr<View> m_view;

public:
	Controller(std::shared_ptr<Model> model, std::shared_ptr<View> view) : m_model(std::move(model)),
																		   m_view(std::move(view))
	{
	}

	void Update()
	{
		HandleInput();
		m_model->UpdateBallPosition();
		m_model->CheckCollisions();
	}

private:
	void HandleInput()
	{
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			m_model->paddle.x -= 0.1f;
		}
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			m_model->paddle.x += 0.1f;
		}
	}
};