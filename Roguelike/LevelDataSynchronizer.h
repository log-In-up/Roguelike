#pragma once

namespace Roguelike
{
	struct PlayerData
	{
		float armor;
		float currentHealth;
		float maxHealth;
	};

	class LevelDataSynchronizer
	{
	private:
		PlayerData* playerData;

	public:
		LevelDataSynchronizer();
		~LevelDataSynchronizer();

		PlayerData& GetPlayerData();
		void SetPlayerData(const PlayerData data);
	};
}