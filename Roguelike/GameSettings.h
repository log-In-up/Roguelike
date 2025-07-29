#pragma once
#include <string>

namespace Arkanoid
{
	class GameWorld
	{
	private:
		GameWorld() = default;
	public:
		static GameWorld& Instance()
		{
			static GameWorld gameWorld;
			return gameWorld;
		}

		// Resources path
		const std::string RESOURCES_PATH = "Resources/";
		const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
		const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
		const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
		const std::string LEVELS_CONFIG_PATH = RESOURCES_PATH + "levels.config";

		// Game settings constants
		const int MAX_APPLES = 80;
		const unsigned int SCREEN_WIDTH = 800;
		const unsigned int SCREEN_HEIGHT = 600;
		const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

		const unsigned int BALL_SIZE = 20;
		const unsigned int BALL_SPEED = 400;

		const unsigned int BONUS_BALL_SIZE = 15;
		const float BONUS_BALL_SPEED = 100.f;

		const unsigned int BLOCK_REWARD = 1;
		const unsigned int THREE_HIT_BLOCK_REWARD = 3;

		const unsigned int PLATFORM_WIDTH = 60;
		const unsigned int PLATFORM_HEIGHT = 20;
		const float PLATFORM_SPEED = 300.f;
		const float PLATFORM_SPEED_INCREASED = 750.f;

		const unsigned int BLOCKS_COUNT_IN_ROW = 15;
		const unsigned int BLOCK_SHIFT = 5;
		const unsigned int BLOCK_WIDTH = (SCREEN_WIDTH - (BLOCKS_COUNT_IN_ROW + 1) * BLOCK_SHIFT) / BLOCKS_COUNT_IN_ROW;
		const unsigned int BLOCK_HEIGHT = 20;

		const int MAX_RECORDS_TABLE_SIZE = 5;
		const char* PLAYER_NAME = "Player";

		const std::string GAME_NAME = "ArkanoidGame";
		const float BREAK_DELAY = 1.f;
		const float BONUS_DURATION = 10.f;
		const int BONUS_PROPABILITY_PERCENT = 10;
	};
}

#define SETTINGS GameWorld::Instance()