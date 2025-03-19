#pragma once

#include "cmath"

class Movable
{
public:
	Movable(float width, float height, float x, float y, float speed, float angle);

	virtual void Update(double elapsedTime);

	void SetBoundingRect(float width, float height)
	{
		m_width = width;
		m_height = height;
	}

	virtual void BeforeUpdate(double elapsedTime)
	{}

	[[nodiscard]] float GetX() const;

	[[nodiscard]] float GetY() const;

	[[nodiscard]] float GetSpeed() const;

	[[nodiscard]] float GetAngle() const;

private:
	void CheckBounds();

protected:
	float m_x = 0;
	float m_y = 0;
	float m_speed = 0;
	float m_angle;

	float m_width = 640;
	float m_height = 480;
};
