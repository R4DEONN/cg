#pragma once

#include "cmath"

class Movable
{
public:
	explicit Movable(float x = 0, float y = 0, float speed = 0, float angle = 0);

	virtual void Update(double elapsedTime);

	[[nodiscard]] float GetX() const;

	[[nodiscard]] float GetY() const;

	[[nodiscard]] float GetSpeed() const;

	[[nodiscard]] float GetAngle() const;

protected:
	float m_x = 0;
	float m_y = 0;
	float m_speed = 0;
	float m_angle;
};
