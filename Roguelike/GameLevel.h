#pragma once
#include <iostream>
#include <array>

#include "Scene.h"
#include "Player.h"
#include "Music.h"
#include "Floor.h"
#include "Wall.h"
#include "LevelLoader.h"
#include "LevelExit.h"
#include "LevelDataSynchronizer.h"

using namespace GameEngine;

namespace Roguelike
{
	const std::string END_LEVEL = "ChangeLevel";

	class GameLevel : public Scene
	{
	private:
		unsigned long long currentLevel;
		LevelLoader& levelLoader;
		std::shared_ptr<LevelExit> exit;
		std::shared_ptr<Player> player;
		std::unique_ptr<Music> music;
		GameEngine::Vector2Df* playerPosition;
		GameEngine::Vector2Df* exitPosition;
		LevelDataSynchronizer* synchronizer;
		std::function<void(GameEngine::Trigger)> onTriggerEnter;
	public:
		std::vector<std::unique_ptr<Wall>>* walls;
		std::vector<std::unique_ptr<Floor>>* floors;
	public:
		GameLevel(LevelLoader& levelLoader);
		~GameLevel();

		void Restart() override;
		void Start() override;
		void Stop() override;
	private:
		void HandleBlock(std::pair<sf::Vector2i, BlockType>& block);
		void PlaceBlock(std::pair<sf::Vector2i, BlockType>& block);
	};
}