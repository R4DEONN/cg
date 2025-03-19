#pragma once

#include "../model/Asteroid.h"
#include "GLApplication.h"

class AsteroidView
{
public:
	void Render(const Asteroid& model, float screenWidth, float screenHeight)
	{
		const auto x = model.GetX();
		const auto y = model.GetY();
		const auto angle = model.GetAngle();
		const float radius = model.GetRadius();


		auto drawAsteroid = [&](float offsetX, float offsetY) {
			glPushMatrix();
			glTranslatef(offsetX, offsetY, 0);
			glRotatef(angle, 0, 0, 1); // Вращение вокруг оси Z

			// Отрисовка астероида как восьмиугольника
			glColor3f(0.5f, 0.5f, 0.5f); // Серый цвет
			glBegin(GL_POLYGON);
			for (int i = 0; i < 8; ++i)
			{
				float angleRad = static_cast<float>(i) * 2.0f * M_PI / 8.0f;
				float vertexX = radius * cos(angleRad);
				float vertexY = radius * sin(angleRad);
				glVertex2f(vertexX, vertexY);
			}
			glEnd();

			glPopMatrix();
		};

		// Отрисовка основного астероида
		drawAsteroid(x, y);

		// Проверка пересечения с правой границей
		if (x + radius > screenWidth)
		{
			drawAsteroid(x - screenWidth, y); // Отрисовка слева
		}

		// Проверка пересечения с левой границей
		if (x - radius < 0)
		{
			drawAsteroid(x + screenWidth, y); // Отрисовка справа
		}

		// Проверка пересечения с нижней границей
		if (y + radius > screenHeight)
		{
			drawAsteroid(x, y - screenHeight); // Отрисовка сверху
		}

		// Проверка пересечения с верхней границей
		if (y - radius < 0)
		{
			drawAsteroid(x, y + screenHeight); // Отрисовка снизу
		}
	}
};
