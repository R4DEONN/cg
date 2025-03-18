//
// Created by admin on 04.03.2025.
//

#include "TetrisController.h"

TetrisController::TetrisController(TetrisModel& model)
	: model(model), lastUpdate(GetTickCount64()) {}

void TetrisController::handleInput(WPARAM key)
{
	switch (key)
	{
	case VK_LEFT:
		model.moveLeft();
		break;
	case VK_RIGHT:
		model.moveRight();
		break;
	case VK_UP:
		model.rotate();
		break;
	case VK_DOWN:
		model.drop();
		break;
	case 'P':
		model.togglePause();
		break;
	case 'R':
		model.restart();
		break;
	}
}

void TetrisController::update() {
	ULONGLONG currentTick = GetTickCount64();
	ULONGLONG interval = 1000 / (1 + model.level); // Уровень влияет на скорость

	if(currentTick - lastUpdate > interval) {
		model.update();
		lastUpdate = currentTick;
	}
}