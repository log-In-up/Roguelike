#include "LevelDataSynchronizer.h"

namespace Roguelike
{
	LevelDataSynchronizer::LevelDataSynchronizer()
	{
		playerData = new PlayerData();

		playerData->armor = 50.f;
		playerData->currentHealth = 100.f;
		playerData->maxHealth = 100.f;
	}

	LevelDataSynchronizer::~LevelDataSynchronizer()
	{
		delete playerData;
	}

	PlayerData& LevelDataSynchronizer::GetPlayerData()
	{
		return *playerData;
	}

	void LevelDataSynchronizer::SetPlayerData(const PlayerData data)
	{
		playerData->armor = data.armor;
		playerData->currentHealth = data.currentHealth;
		playerData->maxHealth = data.maxHealth;
	}
}