//
// Created by admin on 04.04.2025.
//

#pragma once

#include <GL/glu.h>
#include <GL/glut.h>
#include <memory>
#include <utility>
#include "Model.h"

class View
{
private:
	std::shared_ptr<Model> m_model;

public:
	View(std::shared_ptr<Model> model) : m_model(std::move(model)) {}

	void Render()
	{
		glLoadIdentity();
		gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		// Отрисовка шарика
		DrawSphere(m_model->ball.x, m_model->ball.y, m_model->ball.z, m_model->ball.radius);

		// Отрисовка ракетки
		DrawCube(m_model->paddle.x, m_model->paddle.y, m_model->paddle.z,
			m_model->paddle.width, m_model->paddle.height, 0.2f);

		// Отрисовка кирпичей
		for (const auto& brick : m_model->bricks)
		{
			if (brick.health > 0)
			{
				DrawCube(brick.x, brick.y, brick.z, brick.width, brick.height, brick.depth);
			}
		}
	}

private:
	void DrawSphere(float x, float y, float z, float radius)
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidSphere(radius, 20, 20);
		glPopMatrix();
	}

	void DrawCube(float x, float y, float z, float width, float height, float depth)
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(width, height, depth);
		glutSolidCube(1.0f);
		glPopMatrix();
	}
};