#include "AsteroidsModel.h"

void AsteroidsModel::Update()
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

