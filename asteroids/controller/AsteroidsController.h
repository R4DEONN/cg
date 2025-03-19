#pragma once

#include <chrono>
#include "../model/AsteroidsModel.h"
#include "../model/AsteroidManager.h"

class AsteroidsController
{
public:
	AsteroidsController(float width, float height)
		: m_width(width),
		  m_height(height),
		  m_lastFrameTime(std::chrono::steady_clock::now()),
		  m_model(width, height)
	{
	}

	void SetBoundingRect(float width, float height)
	{
		m_width = width;
		m_height = height;
		m_model.SetBoundingRect(width, height);
	}

	void OnKeyboard(unsigned char key, int x, int y);

	void OnKeyboardUp(unsigned char key, int x, int y);

	void OnIdle();

	[[nodiscard]] const AsteroidsModel& GetModel() const
	{
		return m_model;
	}

	[[nodiscard]] const std::vector<Asteroid>& GetAsteroids()
	{
		return m_model.GetAsteroids();
	}

private:
	AsteroidsModel m_model;
	std::chrono::steady_clock::time_point m_lastFrameTime;
	float m_width = 640;
	float m_height = 480;


};
