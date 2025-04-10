#pragma once

#include "Movable.h"

enum class ASTEROID_TYPE
{
	BIG,
	MEDIUM,
	SMALL,
};

class Asteroid : public Movable
{
public:
	Asteroid(float x, float y, float speed, float angle, ASTEROID_TYPE asteroidType)
	: Movable(x, y, speed, angle), m_asteroidType(asteroidType)
	{
	}

	[[nodiscard]] float GetRadius() const
	{
		switch (m_asteroidType)
		{
		case ASTEROID_TYPE::BIG:
			return 15;
		case ASTEROID_TYPE::MEDIUM:
			return 10;
		case ASTEROID_TYPE::SMALL:
			return 5;
		}

		return 0;
	}

private:
	ASTEROID_TYPE m_asteroidType;
};
