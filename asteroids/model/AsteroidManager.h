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
	AsteroidManager(float width, float height)
		: m_width(width),
		  m_height(height)
	{
	}

	void CreateAsteroid()
	{
		SPAWN_BORDER border = GetRandomBorder(m_randomEngine);

		// Генерация координат на выбранной границе
		auto [x, y] = GetSpawnPosition(border);

		// Генерация случайной скорости (от 300 до 500)
		std::uniform_real_distribution<float> speedDist(300, 500);
		float speed = speedDist(m_randomEngine);

		// Генерация угла движения, направленного внутрь экрана
		float angle = GetSpawnAngle(border, m_randomEngine);

		// Создание астероида
		auto newAsteroid = Asteroid(m_width, m_height, x, y, speed, angle, ASTEROID_TYPE::BIG);
		m_asteroids.push_back(newAsteroid);
	}

	void Update(double elapsedTime)
	{
		std::for_each(m_asteroids.begin(), m_asteroids.end(), [elapsedTime] (Asteroid& asteroid) {
			asteroid.Update(elapsedTime);
		});

		m_timeSinceLastCreation += elapsedTime;

		// Если прошла секунда, создаём новый астероид
		if (m_timeSinceLastCreation >= 1.0) // 1.0 секунда
		{
			CreateAsteroid(); // Создаём новый астероид
			m_timeSinceLastCreation = 0; // Обновляем время последнего создания
		}
	}

	void SetBoundingRect(float width, float height)
	{
		m_width = width;
		m_height = height;
		std::for_each(m_asteroids.begin(), m_asteroids.end(), [this] (auto& asteroid) {
			asteroid.SetBoundingRect(m_width, m_height);
		});
	}

	[[nodiscard]] std::vector<Asteroid>& GetAsteroidsData()
	{
		return m_asteroids;
	}

	void Clear()
	{
		m_asteroids.clear();
	}

private:
	std::vector<Asteroid> m_asteroids;
	float m_width = 640;
	float m_height = 480;

	float m_timeSinceLastCreation;
	std::default_random_engine m_randomEngine;

	SPAWN_BORDER GetRandomBorder(std::default_random_engine& randomEngine)
	{
		std::uniform_int_distribution<int> borderDist(0, 3); // 0: TOP, 1: BOTTOM, 2: LEFT, 3: RIGHT
		return static_cast<SPAWN_BORDER>(borderDist(randomEngine));
	}

	std::pair<float, float> GetSpawnPosition(SPAWN_BORDER border)
	{
		std::uniform_real_distribution<float> posDist(0, 1); // Для случайной позиции на границе

		switch (border)
		{
		case SPAWN_BORDER::TOP:
			return { posDist(m_randomEngine) * m_width, -m_height / 2 }; // Верхняя граница
		case SPAWN_BORDER::BOTTOM:
			return { posDist(m_randomEngine) * m_width, m_height / 2 }; // Нижняя граница
		case SPAWN_BORDER::LEFT:
			return { -m_width / 2, posDist(m_randomEngine) * m_height }; // Левая граница
		case SPAWN_BORDER::RIGHT:
			return { m_width / 2, posDist(m_randomEngine) * m_height }; // Правая граница
		default:
			return { 0, 0 }; // По умолчанию (не должно происходить)
		}
	}

	float GetSpawnAngle(SPAWN_BORDER border, std::default_random_engine& randomEngine)
	{
		std::uniform_real_distribution<float> angleDist(0, 90); // Угол отклонения от направления внутрь экрана

		switch (border)
		{
		case SPAWN_BORDER::TOP:
			return 90 + angleDist(randomEngine); // Движение вниз с небольшим отклонением
		case SPAWN_BORDER::BOTTOM:
			return 270 + angleDist(randomEngine); // Движение вверх с небольшим отклонением
		case SPAWN_BORDER::LEFT:
			return 0 + angleDist(randomEngine); // Движение вправо с небольшим отклонением
		case SPAWN_BORDER::RIGHT:
			return 180 + angleDist(randomEngine); // Движение влево с небольшим отклонением
		default:
			return 0; // По умолчанию (не должно происходить)
		}
	}
};
