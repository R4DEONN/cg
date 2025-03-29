#include <iostream>
#include "Movable.h"
#include "cmath"

Movable::Movable(double x, double y, double speed, double angle)
	: m_x(x),
	  m_y(y),
	  m_angle(angle),
	  m_speed(speed)
{
}

void Movable::Update(double elapsedTime)
{
	BeforeUpdate(elapsedTime);
	m_x += m_speed * std::cos(m_angle * M_PI / 180) * elapsedTime;
	m_y += m_speed * std::sin(m_angle * M_PI / 180) * elapsedTime;
	CheckBounds();
}

double Movable::GetSpeed() const
{
	return m_speed;
}

double Movable::GetAngle() const
{
	return m_angle;
}

double Movable::GetY() const
{
	return m_y;
}

double Movable::GetX() const
{
	return m_x;
}

void Movable::CheckBounds()
{
	if (m_x > 1)
	{
		m_x -= 2;
	}
	else if (m_x < -1)
	{
		m_x += 2;
	}

	if (m_y > 1)
	{
		m_y -= 2;
	}
	else if (m_y < -1)
	{
		m_y += 2;
	}
}
