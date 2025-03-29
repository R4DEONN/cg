#pragma once

#include "cmath"

class Movable
{
public:
	Movable(double x, double y, double speed, double angle);

	virtual void Update(double elapsedTime);

	virtual void BeforeUpdate(double elapsedTime)
	{}

	[[nodiscard]] double GetX() const;

	[[nodiscard]] double GetY() const;

	//TODO: не используется
	[[nodiscard]] double GetSpeed() const;

	[[nodiscard]] double GetAngle() const;

private:
	void CheckBounds();

protected:
	double m_x = 0;
	double m_y = 0;
	double m_speed = 0;
	double m_angle;
};
