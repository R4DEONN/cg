#pragma once


#include "PlayerModel.h"
#include "../Disposable.h"
#include "AsteroidManager.h"
#include "windows.h"
#include "Bullet.h"
#include "Constants.h"

class AsteroidsModel
{
public:
	AsteroidsModel() = default;

	void Update()
	{
		auto elapsedTime = GetDeltaTime();
		m_player.Update(elapsedTime);
		m_asteroidManager.Update(elapsedTime);
		std::for_each(m_bullets.begin(), m_bullets.end(), [elapsedTime] (Bullet& bullet) {
			bullet.Update(elapsedTime);
		});
		CheckCollisions();
		CheckBulletAsteroidCollisions();
	}

	[[nodiscard]] const PlayerModel& GetImmutablePlayerModel() const
	{
		return m_player;
	}

	[[nodiscard]] PlayerModel& GetPlayerModel()
	{
		return m_player;
	}

	void PlayerShoot()
	{
		m_bullets.push_back(m_player.Shoot());
	}

	[[nodiscard]] const std::vector<Asteroid>& GetAsteroids() const
	{
		return m_asteroidManager.GetImmutableAsteroids();
	}

	[[nodiscard]] const std::vector<Bullet>& GetBullets() const
	{
		return m_bullets;
	}

	void SetBoundingRect(float width, float height)
	{
		m_width = width;
		m_height = height;
	}


private:
	PlayerModel m_player;
	AsteroidManager m_asteroidManager;
	std::vector<Bullet> m_bullets;
	//TODO: В using Вынести
	//TODO: Сделать так, чтобы пули не улетали и сделать ограничение на макс количество
	std::chrono::steady_clock::time_point m_lastFrameTime;
	double m_width = WIDTH;
	double m_height = HEIGHT;

	float GetDeltaTime()
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration<float>(currentTime - m_lastFrameTime).count();
		m_lastFrameTime = currentTime;
		return deltaTime;
	}

	void CheckCollisions()
	{
		for (const auto& asteroid : m_asteroidManager.GetImmutableAsteroids())
		{
			if (CheckCollision(asteroid))
			{
				OnPlayerDeath();
				break;
			}
		}
	}

	void OnPlayerDeath()
	{
		m_asteroidManager.Clear();
		m_bullets.clear();
		if (m_player.GetLives() <= 0)
		{
			int result = MessageBoxW(
				nullptr,
				L"Начать заново?",
				L"Игра окончена",
				MB_YESNO | MB_ICONQUESTION
			);

			if (result == IDYES)
			{
				m_player.SetLives(3);
				GetDeltaTime();
			}
			else if (result == IDNO)
			{
				exit(0);
			}
		}
		m_player.Respawn();
	}


	bool CheckCollision(const Asteroid& asteroid)
	{
		double playerX = m_player.GetX() * m_width;
		double playerY = m_player.GetY() * m_height;
		double asteroidX = asteroid.GetX() * m_width;
		double asteroidY = asteroid.GetY() * m_height;

		double playerRadius = PlayerModel::GetRadius();
		double asteroidRadius = asteroid.GetRadius();

		double dx = playerX - asteroidX;
		double dy = playerY - asteroidY;
		double distance = std::sqrt(dx * dx + dy * dy);

		return distance < (playerRadius + asteroidRadius);
	}

	[[nodiscard]] bool CheckBulletAsteroidCollision(const Bullet& bullet, const Asteroid& asteroid) const
	{
		double bulletX = bullet.GetX() * m_width;
		double bulletY = bullet.GetY() * m_height;
		double asteroidX = asteroid.GetX() * m_width;
		double asteroidY = asteroid.GetY() * m_height;

		double bulletRadius = Bullet::GetRadius();
		double asteroidRadius = asteroid.GetRadius();

		double dx = bulletX - asteroidX;
		double dy = bulletY - asteroidY;
		double distance = std::sqrt(dx * dx + dy * dy);

		return distance < (bulletRadius + asteroidRadius);
	}

	void CheckBulletAsteroidCollisions()
	{
		auto bulletIt = m_bullets.begin();
		while (bulletIt != m_bullets.end())
		{
			bool bulletDestroyed = false;

			auto asteroidIt = m_asteroidManager.GetAsteroids().begin();
			while (asteroidIt != m_asteroidManager.GetAsteroids().end())
			{
				if (CheckBulletAsteroidCollision(*bulletIt, *asteroidIt))
				{
					asteroidIt = m_asteroidManager.GetAsteroids().erase(asteroidIt);
					bulletIt = m_bullets.erase(bulletIt); //TODO: сделать через два итератора
					bulletDestroyed = true;
					break;
				}
				else
				{
					++asteroidIt;
				}
			}

			if (!bulletDestroyed)
			{
				++bulletIt;
			}
		}
	}
};
