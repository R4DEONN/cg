#include <iostream>
#include "Movable.h"
#include "cmath"

Movable::Movable(float x, float y, float speed, float angle)
	: m_x(x),
	  m_y(y),
	  m_angle(angle),
	  m_speed(speed)
{
}

void Movable::Update(double elapsedTime)
{
	m_x += m_speed * std::cos(m_angle * M_PI / 180) * elapsedTime;
	m_y += m_speed * std::sin(m_angle * M_PI / 180) * elapsedTime;
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
