#include "AsteroidsModel.h"

void AsteroidsModel::Update(double elapsedTime)
{
	m_player.Update(elapsedTime);
//	m_modelUpdatedEvent.Dispatch(*this);
}
