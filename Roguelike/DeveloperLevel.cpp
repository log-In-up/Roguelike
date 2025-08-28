#include "DeveloperLevel.h"
#include "Wall.h"
#include "MazeGenerator.h"
#include "GameSettings.h"

using namespace GameEngine;

namespace Roguelike
{
	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}

	void DeveloperLevel::Start()
	{
		int width = 15;
		int height = 15;

		for (int y = 0; y < height + 1; y++)
		{
			for (int x = 0; x < width + 1; x++)
			{
				GameEngine::Vector2Df spriteSize = std::forward<GameEngine::Vector2Df>({ x * SETTINGS.SPRITE_SIZE, y * SETTINGS.SPRITE_SIZE });

				//if not wall place
				if (x != 0 && x != width && y != 0 && y != height)
				{
					floors.push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(0)));
				}

				//if left-bottom corner
				if (x == 0 && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(25)));
				}

				//if right-bottom corner
				if (x == width && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(27)));
				}

				//if left-top corner
				if (x == 0 && y == height)
				{
					walls.push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(1)));
				}

				//if right-top corner
				if (x == width && y == height)
				{
					walls.push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(3)));
				}

				//if left (not corner)
				if (x == 0 && y != height && y != 0)
				{
					floors.push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(18)));
					walls.push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(12)));
				}

				//if right (not corner)
				if (x == width && y != height && y != 0)
				{
					floors.push_back(std::make_unique<Floor>(spriteSize, std::forward<int>(19)));
					walls.push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(12)));
				}

				//if bottom (not corner)
				if (y == 0 && x != width && x != 0)
				{
					walls.push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(38)));
				}

				//if top (not corner)
				if (y == height && x != width && x != 0)
				{
					walls.push_back(std::make_unique<Wall>(spriteSize, std::forward<int>(38)));
				}
			}
		}

		// Maze Generator
		MazeGenerator mazeGenerator(width, height, this);
		mazeGenerator.Generate();

		player = std::make_unique<Player>(std::forward<GameEngine::Vector2Df>({ width / 2 * SETTINGS.SPRITE_SIZE, height / 2 * SETTINGS.SPRITE_SIZE }));
		music = std::make_unique<Music>("music");
	}

	void DeveloperLevel::Stop()
	{
		GameEngine::GameWorld::Instance()->Clear();
	}
}