#pragma once

#include <iostream>
#include "Movable.h"
#include "Bullet.h"

enum class ROTATE_DIRECTION
{
	LEFT,
	RIGHT,
	NONE,
};

class PlayerModel : public Movable
{
public:
	PlayerModel() : Movable(0, 0, 0, 0)
	{
	}

	void BeforeUpdate(double elapsedTime) override
	{
		Rotate(elapsedTime);
		UpdateSpeed(elapsedTime);
	}

	ROTATE_DIRECTION GetRotation()
	{
		return m_currentRotation;
	}

	void Respawn()
	{
		m_x = 0;
		m_y = 0;
		m_speed = 0;
		m_currentRotation = ROTATE_DIRECTION::NONE;
		m_acceleration = 0;
		m_lives--;
	}

	void SetCurrentRotation(ROTATE_DIRECTION rotateDirection)
	{
		m_currentRotation = rotateDirection;
	}

	void SetEngineEnabled(bool value)
	{
		m_acceleration = value ? ACCELERATION : -ACCELERATION * 3;
	}

	Bullet Shoot()
	{
		return {m_x, m_y, m_angle};
	}

	static float GetRadius()
	{
		return 20.0f;
	}

	[[nodiscard]] int GetLives() const
	{
		return m_lives;
	}

	void SetLives(int value)
	{
		m_lives = value;
	}

private:
	static constexpr const double ROTATE_SPEED = 180;
	static constexpr const double ACCELERATION = 0.5;
	static constexpr const double MAX_SPEED = 1;
	static constexpr const double MIN_SPEED = 0;

	ROTATE_DIRECTION m_currentRotation = ROTATE_DIRECTION::NONE;
	double m_acceleration = 0;
	int m_lives = 0;

	void UpdateSpeed(double elapsedTime)
	{
		m_speed += m_acceleration * elapsedTime;
		m_speed = std::clamp(m_speed, MIN_SPEED, MAX_SPEED);
	}

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

		NormalizeAngle();
	}

	void NormalizeAngle()
	{
		m_angle = std::fmod(m_angle, 360.0f);
		if (m_angle < 0.0f)
		{
			m_angle += 360.0f;
		}
	}
};
