#pragma once

#include <iostream>
#include "Movable.h"

enum class ROTATE_DIRECTION
{
	LEFT,
	RIGHT,
	NONE,
};

class PlayerModel : public Movable
{
public:
	//TODO: Щаблонный метод в родителе
	void Update(double elapsedTime) override
	{
		Rotate(elapsedTime);
		UpdateSpeed(elapsedTime);
		Movable::Update(elapsedTime);
	}

	//TODO: приватным
	void Rotate(double elapsedTime)
	{
		float rotate = 0;
		switch (m_currentRotation)
		{
		case ROTATE_DIRECTION::RIGHT:
			rotate = ROTATE_SPEED;
			break;
		case ROTATE_DIRECTION::LEFT:
			rotate = -ROTATE_SPEED;
			break;
		case ROTATE_DIRECTION::NONE:
			break;
		}
		rotate *= elapsedTime;
		m_angle += rotate;

		//TODO: fmod || modf
		if (m_angle >= 360.0f)
		{
			m_angle -= 360.0f;
		}
		else if (m_angle < 0.0f)
		{
			m_angle += 360.0f;
		}
	}

	ROTATE_DIRECTION GetRotation()
	{
		return m_currentRotation;
	}

	void SetCurrentRotation(ROTATE_DIRECTION rotateDirection)
	{
		m_currentRotation = rotateDirection;
	}

	void SetEngineEnabled(bool value)
	{
		if (value)
		{
			m_acceleration = ACCELERATION;
		}
		else
		{
			m_acceleration = -ACCELERATION;
		}
	}

private:
	static constexpr const float ROTATE_SPEED = 180;
	static constexpr const float ACCELERATION = 150;

	ROTATE_DIRECTION m_currentRotation = ROTATE_DIRECTION::NONE;
	float m_acceleration = -ACCELERATION;

	void UpdateSpeed(double elapsedTime)
	{
		m_speed += m_acceleration * elapsedTime;

		if (m_speed < 0)
		{
			m_speed = 0;
		}
	}
};
