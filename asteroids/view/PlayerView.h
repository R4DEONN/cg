#pragma once
#include <GL/glut.h>
#include "../model/PlayerModel.h"

class PlayerView
{
public:
	PlayerView()
	{}

	void Render(const PlayerModel& model, float screenWidth, float screenHeight);
private:
};
