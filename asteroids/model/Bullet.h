#pragma once


#include "Movable.h"

class Bullet : public Movable
{
public:
	Bullet(float width, float height, float x, float y, float angle)
		: Movable(width, height, x, y, 300, angle)
	{
	}

	float GetRadius() const
	{
		return 2;
	}
};
