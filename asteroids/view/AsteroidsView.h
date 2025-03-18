#pragma once
#include "GLApplication.h"
#include "../controller/AsteroidsController.h"
#include "PlayerView.h"

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
};
