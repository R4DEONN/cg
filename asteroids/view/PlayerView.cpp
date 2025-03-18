#include <iostream>
#include "PlayerView.h"

void PlayerView::Render(const PlayerModel& model)
{
	const auto x = model.GetX();
	const auto y = model.GetY();
	const auto angle = model.GetAngle();

	glPushMatrix();

	glTranslatef(x, y, 0);

	glRotatef(angle, 0, 0, 1); // Вращение вокруг оси Z

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(10, 0);
	glVertex2f(-10, 10);
	glVertex2f(-10, -10);
	glEnd();

	glPopMatrix();
}
