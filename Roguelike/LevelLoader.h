#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Block.h"
#include "ThreeHitBlock.h"

namespace Arkanoid
{
	enum class BlockType
	{
		Simple,
		ThreeHit,
		Unbreackable
	};

	struct Level
	{
		std::vector<std::pair<sf::Vector2i, BlockType>> m_blocks;
	};

	class LevelLoader final
	{
	private:
		std::vector<Level>* levels;
	public:
		LevelLoader();
		~LevelLoader();

		int GetLevelCount();
		Level& GetLevel(int i);
	private:
		static BlockType CharToBlockType(char symbol);
		void LoadLevelsFromFile();
	};
}
