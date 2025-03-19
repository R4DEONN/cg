#pragma once


#include "PlayerModel.h"
#include "../Disposable.h"
#include "AsteroidManager.h"
#include "windows.h"
#include "Bullet.h"

class AsteroidsModel
{
public:
	AsteroidsModel(float width, float height)
	: m_player(width, height),
		m_asteroidManager(width, height)
	{

	}

	void SetBoundingRect(float width, float height)
	{
		m_player.SetBoundingRect(width, height);
		m_asteroidManager.SetBoundingRect(width, height);
		std::for_each(m_bullets.begin(), m_bullets.end(), [width, height] (Bullet& bullet) {
			bullet.SetBoundingRect(width, height);
		});
	}

	void Update();

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

	void CheckCollisions()
	{
		for (const auto& asteroid : m_asteroidManager.GetAsteroidsData())
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
		float dx = m_player.GetX() - asteroid.GetX();
		float dy = m_player.GetY() - asteroid.GetY();
		float distance = std::sqrt(dx * dx + dy * dy);

		float radiusSum = m_player.GetRadius() + asteroid.GetRadius();

		return distance < radiusSum;
	}

	[[nodiscard]] std::vector<Asteroid>& GetAsteroids()
	{
		return m_asteroidManager.GetAsteroidsData();
	}

	const std::vector<Bullet>& GetBullets() const
	{
		return m_bullets;
	}

private:
	PlayerModel m_player;
	AsteroidManager m_asteroidManager;
	std::vector<Bullet> m_bullets;
	std::chrono::steady_clock::time_point m_lastFrameTime;

	float GetDeltaTime()
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration<float>(currentTime - m_lastFrameTime).count();
		m_lastFrameTime = currentTime;
		return deltaTime;
	}

	bool CheckBulletAsteroidCollision(const Bullet& bullet, const Asteroid& asteroid)
	{
		float dx = bullet.GetX() - asteroid.GetX();
		float dy = bullet.GetY() - asteroid.GetY();
		float distance = std::sqrt(dx * dx + dy * dy);

		float radiusSum = bullet.GetRadius() + asteroid.GetRadius();

		return distance < radiusSum;
	}

	void CheckBulletAsteroidCollisions()
	{
		auto bulletIt = m_bullets.begin();
		while (bulletIt != m_bullets.end())
		{
			bool bulletDestroyed = false;

			auto asteroidIt = m_asteroidManager.GetAsteroidsData().begin();
			while (asteroidIt != m_asteroidManager.GetAsteroidsData().end())
			{
				if (CheckBulletAsteroidCollision(*bulletIt, *asteroidIt))
				{
					asteroidIt = m_asteroidManager.GetAsteroidsData().erase(asteroidIt);
					bulletIt = m_bullets.erase(bulletIt);
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
