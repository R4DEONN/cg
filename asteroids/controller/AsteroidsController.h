#pragma once

#include <chrono>
#include "../model/AsteroidsModel.h"

class AsteroidsController
{
public:
	AsteroidsController()
	{
		m_lastFrameTime = std::chrono::steady_clock::now();
	}

	void OnKeyboard(unsigned char key, int x, int y);
	void OnKeyboardUp(unsigned char key, int x, int y);
	void OnIdle();

	[[nodiscard]] const AsteroidsModel& GetModel()
	{
		return m_model;
	}

private:
	AsteroidsModel m_model;
	std::chrono::steady_clock::time_point m_lastFrameTime;

	float GetDeltaTime()
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration<float>(currentTime - m_lastFrameTime).count();
		m_lastFrameTime = currentTime;
		return deltaTime;
	}
};
