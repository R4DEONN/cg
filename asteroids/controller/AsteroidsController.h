#pragma once

#include <chrono>
#include "../model/AsteroidsModel.h"
#include "../model/AsteroidManager.h"

class AsteroidsController
{
public:
	AsteroidsController()
		: m_lastFrameTime(std::chrono::steady_clock::now())
	{
	}

	void OnKeyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 'A':
		case 'a':
			m_model.GetPlayerModel().SetCurrentRotation(ROTATE_DIRECTION::LEFT);
			return;
		case 'D':
		case 'd':
			m_model.GetPlayerModel().SetCurrentRotation(ROTATE_DIRECTION::RIGHT);
			return;
		case 'W':
		case 'w':
			m_model.GetPlayerModel().SetEngineEnabled(true);
			return;
		case ' ':
			m_model.PlayerShoot();
			return;
		default:
			return;
		}
	}

	void OnKeyboardUp(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 'A':
		case 'a':
			if (m_model.GetPlayerModel().GetRotation() == ROTATE_DIRECTION::LEFT)
			{
				m_model.GetPlayerModel().SetCurrentRotation(ROTATE_DIRECTION::NONE);
			}
			return;
		case 'D':
		case 'd':
			if (m_model.GetPlayerModel().GetRotation() == ROTATE_DIRECTION::RIGHT)
			{
				m_model.GetPlayerModel().SetCurrentRotation(ROTATE_DIRECTION::NONE);
			}
			return;
		case 'w':
			m_model.GetPlayerModel().SetEngineEnabled(false);
			return;
		default:
			return;
		}
	}

	void OnIdle()
	{
		m_model.Update();
	}

	[[nodiscard]] const AsteroidsModel& GetModel() const
	{
		return m_model;
	}

	[[nodiscard]] AsteroidsModel& GetMutableModel()
	{
		return m_model;
	}

private:
	AsteroidsModel m_model;
	std::chrono::steady_clock::time_point m_lastFrameTime;
};
