#pragma once
#include <GL/glut.h>
#include "../model/PlayerModel.h"

class PlayerView
{
public:
	static void Render(const PlayerModel& model, float screenWidth, float screenHeight)
	{
		const auto x = model.GetX() * screenWidth / 2;
		const auto y = model.GetY() * screenHeight / 2;
		const auto angle = model.GetAngle();

		const float vertex1X = 10;
		const float vertex1Y = 0;
		const float vertex2X = -10;
		const float vertex2Y = 10;
		const float vertex3X = -10;
		const float vertex3Y = -10;

		auto drawTriangle = [&](float offsetX, float offsetY) {
			glPushMatrix();
			glTranslatef(offsetX, offsetY, 0);
			glRotatef(angle, 0, 0, 1); // Вращение вокруг оси Z

			glColor3f(1, 1, 1); // Белый цвет
			glBegin(GL_TRIANGLES);
			glVertex2f(vertex1X, vertex1Y);
			glVertex2f(vertex2X, vertex2Y);
			glVertex2f(vertex3X, vertex3Y);
			glEnd();

			glPopMatrix();
		};

		drawTriangle(x, y);

		if (x + vertex1X > screenWidth / 2 || x + vertex2X > screenWidth / 2 || x + vertex3X > screenWidth / 2)
		{
			drawTriangle(x - screenWidth, y); // Отрисовка слева
		}

		if (x + vertex1X < -screenWidth / 2 || x + vertex2X < -screenWidth / 2 || x + vertex3X < -screenWidth / 2)
		{
			drawTriangle(x + screenWidth, y); // Отрисовка справа
		}

		if (y + vertex1Y > screenHeight / 2 || y + vertex2Y > screenHeight / 2 || y + vertex3Y > screenHeight / 2)
		{
			drawTriangle(x, y - screenHeight); // Отрисовка сверху
		}

		if (y + vertex1Y < -screenHeight / 2 || y + vertex2Y < -screenHeight / 2 || y + vertex3Y < -screenHeight / 2)
		{
			drawTriangle(x, y + screenHeight); // Отрисовка снизу
		}
	}
};
