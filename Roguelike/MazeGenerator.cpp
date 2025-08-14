#include <cstdlib>
#include <ctime>

#include "MazeGenerator.h"
#include "DeveloperLevel.h"

namespace Roguelike
{
	MazeGenerator::MazeGenerator(int width, int height, DeveloperLevel* level)
		: width(width), height(height), level(level)
	{
		grid.resize(height, std::vector<bool>(width, false));
	}

	void MazeGenerator::Generate()
	{
		std::srand((unsigned int)std::time(nullptr));

		int startX = std::rand() % width;
		int startY = std::rand() % height;

		std::stack<std::pair<int, int>> stack;
		stack.push({ startX, startY });
		grid[startY][startX] = true;

		while (!stack.empty())
		{
			auto [x, y] = stack.top();
			stack.pop();

			std::vector<std::pair<int, int>> directions = GetAvailableDirections(x, y);

			if (!directions.empty())
			{
				stack.push({ x, y });

				std::pair<int, int> dir = directions[std::rand() % directions.size()];
				int nx = x + dir.first;
				int ny = y + dir.second;

				RemoveWall(x, y, nx, ny);

				grid[ny][nx] = true;
				stack.push({ nx, ny });
			}
		}
	}

	std::vector<std::pair<int, int>> MazeGenerator::GetAvailableDirections(int x, int y)
	{
		std::vector<std::pair<int, int>> directions = {
			{0, -2}, // Up
			{0, 2},  // Down
			{-2, 0}, // Left
			{2, 0}   // Right
		};

		std::vector<std::pair<int, int>> available;

		for (const auto& dir : directions)
		{
			int nx = x + dir.first;
			int ny = y + dir.second;

			if (nx >= 0 && nx < width && ny >= 0 && ny < height && !grid[ny][nx])
			{
				available.push_back(dir);
			}
		}

		return available;
	}

	void MazeGenerator::RemoveWall(int x1, int y1, int x2, int y2)
	{
		int wallX = (x1 + x2) / 2;
		int wallY = (y1 + y2) / 2;

		level->floors.push_back(std::make_unique<Floor>(
			GameEngine::Vector2Df{ x1 * 128.f, y1 * 128.f }, 0));
		level->floors.push_back(std::make_unique<Floor>(
			GameEngine::Vector2Df{ x2 * 128.f, y2 * 128.f }, 0));

		if (wallX != x1 || wallY != y1)
		{
			level->walls.push_back(std::make_unique<Wall>(
				GameEngine::Vector2Df{ wallX * 128.f, wallY * 128.f }, 14));
		}
	}
}