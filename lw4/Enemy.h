#pragma once

#include "MazeModel.h"
#include "EnemySound.h"
#include <cmath>

class Enemy
{
public:
	Enemy(float startX, float startZ, float speed = 1.0f)
		: m_x(startX), m_z(startZ), m_speed(speed), m_rotationAngle(0.0f)
	{
	}

	void Update(const MazeModel& mazeModel, float deltaTime)
	{
		m_enemySound.Update();
		float playerX = mazeModel.GetCamX();
		float playerZ = mazeModel.GetCamZ();

		float dx = playerX - m_x;
		float dz = playerZ - m_z;

		m_rotationAngle = atan2f(dx, dz) * (180.0f / M_PI);

		float distance = sqrt(dx * dx + dz * dz);
		if (distance > 0)
		{
			dx /= distance;
			dz /= distance;
		}

		float newX = m_x + dx * m_speed * deltaTime;
		float newZ = m_z + dz * m_speed * deltaTime;

		if (!mazeModel.IsWall(newX, m_z))
		{
			m_x = newX;
		}
		if (!mazeModel.IsWall(m_x, newZ))
		{
			m_z = newZ;
		}
	}

	[[nodiscard]] float GetX() const { return m_x; }
	[[nodiscard]] float GetZ() const { return m_z; }
	[[nodiscard]] float GetY() const { return MazeModel::CELL_SIZE / 2.0f - 0.5; }
	[[nodiscard]] float GetRotation() const { return m_rotationAngle; }

private:
	float m_x, m_z;
	float m_speed;
	float m_rotationAngle;
	EnemySound m_enemySound;
};