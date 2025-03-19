#pragma once

#include "GLApplication.h"
#include "../controller/AsteroidsController.h"
#include "PlayerView.h"
#include "AsteroidView.h"
#include "BulletView.h"

class AsteroidsView : public CGLApplication
{
public:
	explicit AsteroidsView(const char* title);

private:
	void OnInit() override;
	void OnDisplay() override;
	void OnReshape(int width, int height) override;
	void OnIdle() override;
	void OnKeyboard(unsigned char key, int x, int y) override;
	void OnKeyboardUp(unsigned char key, int x, int y) override;

	AsteroidsController m_controller;
	PlayerView m_playerView;
	AsteroidView m_asteroidView;
	BulletView m_bulletView;
	float m_width = 640;
	float m_height = 480;
};
