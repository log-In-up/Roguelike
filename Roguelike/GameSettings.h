#pragma once
#include <string>

namespace Roguelike
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
		const unsigned int SCREEN_WIDTH = 1280;
		const unsigned int SCREEN_HEIGHT = 720;
		const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

		const int MAX_RECORDS_TABLE_SIZE = 5;
		const char* PLAYER_NAME = "Player";

		const std::string GAME_NAME = "Roguelike";

		const float SPRITE_SIZE = 128.f;
	};
}

#define SETTINGS GameWorld::Instance()