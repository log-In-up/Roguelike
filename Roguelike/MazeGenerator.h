#pragma once
#include <vector>
#include <stack>

#include "DeveloperLevel.h"

namespace Roguelike
{
	class MazeGenerator
	{
	private:
		int width, height;
		DeveloperLevel* level;
		std::vector<std::vector<bool>> grid;
	public:
		MazeGenerator(int width, int height, DeveloperLevel* level);
		void Generate();
	private:
		std::vector<std::pair<int, int>> GetAvailableDirections(int x, int y);
		void RemoveWall(int x1, int y1, int x2, int y2);
	};
}