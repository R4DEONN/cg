#include <GL/glut.h>
#include "AsteroidsController.h"

void AsteroidsController::OnIdle()
{
	m_model.Update(GetDeltaTime());
}

void AsteroidsController::OnKeyboard(unsigned char key, int x, int y)
{
	std::cout << "Mew" << std::endl;
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
	}
}

void AsteroidsController::OnKeyboardUp(unsigned char key, int x, int y)
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
	}
}
