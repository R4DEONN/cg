#include <iostream>
#include "Movable.h"
#include "cmath"

Movable::Movable(float width, float height, float x, float y, float speed, float angle)
	: m_x(x),
	  m_y(y),
	  m_angle(angle),
	  m_speed(speed),
	  m_width(width),
	  m_height(height)
{
}

void Movable::Update(double elapsedTime)
{
	BeforeUpdate(elapsedTime);
	m_x += m_speed * std::cos(m_angle * M_PI / 180) * elapsedTime;
	m_y += m_speed * std::sin(m_angle * M_PI / 180) * elapsedTime;
	CheckBounds();
}

float Movable::GetSpeed() const
{
	return m_speed;
}

float Movable::GetAngle() const
{
	return m_angle;
}

float Movable::GetY() const
{
	return m_y;
}

float Movable::GetX() const
{
	return m_x;
}

void Movable::CheckBounds()
{
	if (m_x > m_width / 2)
	{
		m_x -= m_width;
	}
	else if (m_x < -m_width / 2)
	{
		m_x += m_width;
	}

	if (m_y > m_height / 2)
	{
		m_y -= m_height;
	}
	else if (m_y < -m_height / 2)
	{
		m_y += m_height;
	}
}
