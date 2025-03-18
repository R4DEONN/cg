//
// Created by admin on 04.03.2025.
//

#pragma once
#include "TetrisModel.h"
#include "framework.h"

class TetrisController {
public:
	TetrisController(TetrisModel& model);

	void handleInput(WPARAM key);
	void update();

private:
	TetrisModel& model;
	ULONGLONG lastUpdate;
};