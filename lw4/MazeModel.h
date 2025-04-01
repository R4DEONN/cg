#pragma once

#include <valarray>
#include <iostream>

class MazeModel
{
public:
	static constexpr float CELL_SIZE = 5.0f;
	static constexpr float PLAYER_RADIUS = 0.3f;

	[[nodiscard]] auto GetMaze() const
	{
		return m_maze;
	}

	static int GetMazeSize()
	{
		return m_mazeSize;
	}

	[[nodiscard]] float GetCamX() const
	{
		return m_camX;
	}

	[[nodiscard]] float GetCamY() const
	{
		return m_camY;
	}

	[[nodiscard]] float GetCamZ() const
	{
		return m_camZ;
	}

	[[nodiscard]] float GetAngleY() const
	{
		return m_angleY;
	}

	//TODO: Вынести лабиринт отсюда
	void MoveCamera(float speed)
	{
		float dx = std::cos(m_angleY * (M_PI / 180.0f)) * speed;
		float dz = std::sin(m_angleY * (M_PI / 180.0f)) * speed;

		HandleCollisions(dx, dz);

		//TODO: elapsedTime
		m_camX += dx;
		m_camZ += dz;
	}

	void MoveCameraStrafe(float speed)
	{
		m_angleY += 90;
		MoveCamera(speed);
		m_angleY -= 90;
	}

	void RotateCamera(float dAngle)
	{
		m_angleY += dAngle;
		NormalizeAngle();
	}

	[[nodiscard]] bool IsWall(float x, float z) const
	{
		int gridX = static_cast<int>(std::floor(x / CELL_SIZE));
		int gridZ = static_cast<int>(std::floor(z / CELL_SIZE));

		if (gridX < 0 || gridX >= m_mazeSize || gridZ < 0 || gridZ >= m_mazeSize)
		{
			return false;
		}

		return m_maze[gridX][gridZ] == 1;
	}

private:
	static const int m_mazeSize = 16;
	int m_maze[m_mazeSize][m_mazeSize] = {
		{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1 },
		{ 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	float m_camX = -10.0f, m_camY = 1.0f, m_camZ = 7 * CELL_SIZE;
	float m_angleY = 0.0f;

	void HandleCollisions(float& dx, float& dz)
	{
		float newX = m_camX + dx;
		float newZ = m_camZ + dz;

		if (IsWall(newX + PLAYER_RADIUS + dx, m_camZ) || IsWall(newX - PLAYER_RADIUS + dx, m_camZ))
		{
			dx = 0;
		}
		if (IsWall(m_camX, newZ + PLAYER_RADIUS +dz) ||IsWall(m_camX, newZ - PLAYER_RADIUS + dz     ))
		{
			dz = 0;
		}
	}

		void NormalizeAngle()
	{
		m_angleY = std::fmod(m_angleY, 360.0f);
		if (m_angleY < 0.0f)
		{
			m_angleY += 360.0f;
		}
	}
};
