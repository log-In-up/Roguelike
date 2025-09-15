#include <cassert>
#include <Vector.h>
#include <Trigger.h>
#include <functional>

#include "GameLevel.h"
#include "GameSettings.h"
#include "Application.h"
#include <SpriteColliderComponent.h>

namespace Roguelike
{
	GameLevel::GameLevel(LevelLoader& levelLoader) : levelLoader(levelLoader)
	{
		currentLevel = 0;

		walls = new std::vector<std::unique_ptr<Wall>>();
		floors = new std::vector<std::unique_ptr<Floor>>();

		playerPosition = new GameEngine::Vector2Df(0.f, 0.f);
		exitPosition = new GameEngine::Vector2Df(0.f, 0.f);

		synchronizer = new LevelDataSynchronizer();
	}

	GameLevel::~GameLevel()
	{
		delete walls;
		delete floors;

		delete playerPosition;
		delete exitPosition;

		delete synchronizer;
	}

	void GameLevel::Restart()
	{
		Stop();
		Start();
	}

	void GameLevel::Start()
	{
		LevelData levelData = levelLoader.GetLevelData(currentLevel);

		for (std::pair<sf::Vector2i, BlockType> block : levelData.blocks)
		{
			PlaceBlock(block);

			HandleBlock(block);
		}

		exit = std::make_unique<LevelExit>(*exitPosition);

		PlayerData data = synchronizer->GetPlayerData();
		player = std::make_unique<Player>(*playerPosition, data);

		onTriggerEnter = std::function<void(GameEngine::Trigger)>(
			[this](GameEngine::Trigger trigger)
			{
				if (trigger.GetSecondComponent().GetGameObject()->GetName() != "Player")
				{
					return;
				}

				currentLevel++;

				if (currentLevel >= levelLoader.GetLevelCount())
				{
					currentLevel = 0;
				}

				Restart();
			}
		);

		auto exitCollision = exit.get()->GetGameObject().GetComponent<GameEngine::SpriteColliderComponent>();
		exitCollision->SubscribeTriggerEnter(onTriggerEnter);

		music = std::make_unique<Music>("music");
	}

	void GameLevel::Stop()
	{
		PlayerData data = player.get()->GetPlayerData();
		synchronizer->SetPlayerData(data);

		auto exitCollision = exit.get()->GetGameObject().GetComponent<GameEngine::SpriteColliderComponent>();
		exitCollision->UnsubscribeAllTriggerEnters();

		GameEngine::GameWorld::Instance()->Clear();
	}

	void GameLevel::HandleBlock(std::pair<sf::Vector2i, BlockType>& block)
	{
		switch (block.second)
		{
		case BlockType::BossSpawn:
			break;
		case BlockType::Exit:
			exitPosition->x = block.first.x * SETTINGS.SPRITE_SIZE;
			exitPosition->y = block.first.y * SETTINGS.SPRITE_SIZE;
			break;
		case BlockType::Floor:
			break;
		case BlockType::PlayerSpawn:
			playerPosition->x = block.first.x * SETTINGS.SPRITE_SIZE;
			playerPosition->y = block.first.y * SETTINGS.SPRITE_SIZE;
			break;
		case BlockType::BottomWall:
			break;
		case BlockType::LeftWall:
			break;
		case BlockType::RightWall:
			break;
		case BlockType::TopWall:
			break;
		case BlockType::LeftTopCorner:
			break;
		case BlockType::LeftBottomCorner:
			break;
		case BlockType::RightTopCorner:
			break;
		case BlockType::RightBottomCorner:
			break;
		default:
			assert(false);
			break;
		}
	}

	void GameLevel::PlaceBlock(std::pair<sf::Vector2i, BlockType>& block)
	{
		GameEngine::Vector2Df spriteSize = std::forward<GameEngine::Vector2Df>({ block.first.x * SETTINGS.SPRITE_SIZE, block.first.y * SETTINGS.SPRITE_SIZE });

		switch (block.second)
		{
		case BlockType::BossSpawn:
			floors->push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(0)));
			break;
		case BlockType::Exit:
			floors->push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(16)));
			break;
		case BlockType::Floor:
			floors->push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(0)));
			break;
		case BlockType::PlayerSpawn:
			floors->push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(0)));
			break;
		case BlockType::BottomWall:
			walls->push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(38)));
			break;
		case BlockType::LeftWall:
			floors->push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(18)));
			walls->push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(12)));
			break;
		case BlockType::RightWall:
			floors->push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(19)));
			walls->push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(12)));
			break;
		case BlockType::TopWall:
			walls->push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(38)));
			break;
		case BlockType::LeftTopCorner:
			walls->push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(25)));
			break;
		case BlockType::LeftBottomCorner:
			walls->push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(1)));
			break;
		case BlockType::RightTopCorner:
			walls->push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(27)));
			break;
		case BlockType::RightBottomCorner:
			walls->push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(3)));
			break;
		default:
			assert(false);
			break;
		}
	}
}