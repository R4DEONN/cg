#pragma once


#include "PlayerModel.h"
#include "../Disposable.h"

class AsteroidsModel
{
public:
	AsteroidsModel() = default;

	void Update(double elapsedTime);

	[[nodiscard]] const PlayerModel& GetImmutablePlayerModel() const
	{
		return m_player;
	}

	[[nodiscard]] PlayerModel& GetPlayerModel()
	{
		return m_player;
	}

	[[nodiscard]] auto& ModelUpdatedEvent() const
	{
		return m_modelUpdatedEvent;
	}

private:
	PlayerModel m_player;
	mutable EventDispatcher<AsteroidsModel> m_modelUpdatedEvent;
};
