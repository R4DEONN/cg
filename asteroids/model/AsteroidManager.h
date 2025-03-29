#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include "Asteroid.h"

enum class SPAWN_BORDER
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

class AsteroidManager
{
public:
	AsteroidManager() = default;

	void CreateAsteroid()
	{
		SPAWN_BORDER border = GetRandomBorder(m_randomEngine);

		auto [x, y] = GetSpawnPosition(border);

		std::uniform_real_distribution<float> speedDist(0.25, .5);
		float speed = speedDist(m_randomEngine);

		float angle = GetSpawnAngle(border, m_randomEngine);

		auto newAsteroid = Asteroid(x, y, speed, angle, ASTEROID_TYPE::BIG);
		m_asteroids.push_back(newAsteroid);
	}

	void Update(double elapsedTime)
	{
		std::for_each(m_asteroids.begin(), m_asteroids.end(), [elapsedTime] (Asteroid& asteroid) {
			asteroid.Update(elapsedTime);
		});

		m_timeSinceLastCreation += elapsedTime;

		if (m_timeSinceLastCreation >= 1.5)
		{
			CreateAsteroid();
			m_timeSinceLastCreation = 0;
		}
	}

	[[nodiscard]] const std::vector<Asteroid>& GetImmutableAsteroids() const
	{
		return m_asteroids;
	}

	[[nodiscard]] std::vector<Asteroid>& GetAsteroids()
	{
		return m_asteroids;
	}

	void Clear()
	{
		m_asteroids.clear();
	}

private:
	std::vector<Asteroid> m_asteroids;

	double m_timeSinceLastCreation{};
	std::default_random_engine m_randomEngine;

	static SPAWN_BORDER GetRandomBorder(std::default_random_engine& randomEngine)
	{
		std::uniform_int_distribution<int> borderDist(0, 3);
		return static_cast<SPAWN_BORDER>(borderDist(randomEngine));
	}

	std::pair<float, float> GetSpawnPosition(SPAWN_BORDER border)
	{
		std::uniform_real_distribution<float> posDist(-1, 1);

		switch (border)
		{
		case SPAWN_BORDER::TOP:
			return { posDist(m_randomEngine), -1 };
		case SPAWN_BORDER::BOTTOM:
			return { posDist(m_randomEngine), 1 };
		case SPAWN_BORDER::LEFT:
			return { -1, posDist(m_randomEngine) };
		case SPAWN_BORDER::RIGHT:
			return { 1, posDist(m_randomEngine) };
		default:
			return { 0, 0 };
		}
	}

	float GetSpawnAngle(SPAWN_BORDER border, std::default_random_engine& randomEngine)
	{
		std::uniform_real_distribution<float> angleDist(0, 90);

		switch (border)
		{
		case SPAWN_BORDER::TOP:
			return 90 + angleDist(randomEngine);
		case SPAWN_BORDER::BOTTOM:
			return 270 + angleDist(randomEngine);
		case SPAWN_BORDER::LEFT:
			return 0 + angleDist(randomEngine);
		case SPAWN_BORDER::RIGHT:
			return 180 + angleDist(randomEngine);
		default:
			return 0;
		}
	}
};
