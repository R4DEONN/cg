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
	PlayerModel(float width, float height) : Movable(width, height, 0, 0, 0, 0)
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
		return {m_width, m_height, m_x, m_y, m_angle};
	}

	float GetRadius()
	{
		return 10.0f;
	}

	int GetLives()
	{
		return m_lives;
	}

	void SetLives(int value)
	{
		m_lives = value;
	}

private:
	static constexpr const float ROTATE_SPEED = 180;
	static constexpr const float ACCELERATION = 150;
	static constexpr const float MAX_SPEED = 500;
	static constexpr const float MIN_SPEED = 0;

	ROTATE_DIRECTION m_currentRotation = ROTATE_DIRECTION::NONE;
	float m_acceleration = 0;
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
