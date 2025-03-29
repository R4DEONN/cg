#pragma once


#include <GL/gl.h>
#include <iostream>
#include "../model/Bullet.h"

class BulletView
{
public:
	static void Render(const Bullet& model, float screenWidth, float screenHeight)
	{
		const auto x = model.GetX() * screenWidth / 2;
		const auto y = model.GetY() * screenHeight / 2;

		float renderX = x;
		float renderY = y;

		if (x < -screenWidth / 2) renderX += screenWidth;
		if (x > screenWidth / 2) renderX -= screenWidth;
		if (y < -screenHeight/2) renderY += screenHeight;
		if (y > screenHeight /2) renderY -= screenHeight;

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2f(renderX - 1, renderY - 1); // Левый нижний угол
		glVertex2f(renderX + 1, renderY - 1); // Правый нижний угол
		glVertex2f(renderX + 1, renderY + 1); // Правый верхний угол
		glVertex2f(renderX - 1, renderY + 1); // Левый верхний угол
		glEnd();
	}
};
