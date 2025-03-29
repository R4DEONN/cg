#pragma once


#include "../model/AsteroidsModel.h"
#include "PlayerView.h"
#include "BulletView.h"
#include "AsteroidView.h"

class Renderer
{
public:
	Renderer(float screenWidth, float screenHeight)
		: m_screenWidth(screenWidth), m_screenHeight(screenHeight)
	{
	}

	void Render(const AsteroidsModel& model)
	{
		const auto& player = model.GetImmutablePlayerModel();
		PlayerView::Render(player, m_screenWidth, m_screenHeight);

		std::for_each(
			model.GetBullets().begin(),
			model.GetBullets().end(),
			[this](const Bullet& bullet)
			{
				BulletView::Render(bullet, m_screenWidth, m_screenHeight);
			}
		);

		std::for_each(
			model.GetAsteroids().begin(),
			model.GetAsteroids().end(),
			[this](const Asteroid& asteroid)
			{
				AsteroidView::Render(asteroid, m_screenWidth, m_screenHeight);
			}
		);
	}

	void SetBoundingRect(float width, float height)
	{
		m_screenWidth = width;
		m_screenHeight = height;
	}

private:
	float m_screenWidth = 0.0f;
	float m_screenHeight = 0.0f;
};
