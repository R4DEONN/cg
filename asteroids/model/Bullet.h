#pragma once

#include "Movable.h"

class Bullet : public Movable
{
public:
	Bullet(double x, double y, double angle)
		: Movable(x, y, 1, angle)
	{
	}

	static double GetRadius()
	{
		return 5;
	}
};
