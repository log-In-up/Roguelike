#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <SFML/System/Vector2.hpp>

namespace Roguelike
{
	const std::string EXTENSION(".config");

	enum class BlockType
	{
		BossSpawn, //-> O
		Exit, //-> E
		Floor, //-> F
		PlayerSpawn, //-> P
		BottomWall, //-> B
		LeftWall, //-> L
		RightWall, //-> R
		TopWall, //-> T
		LeftTopCorner,//-> 7
		LeftBottomCorner, //-> 1
		RightTopCorner,//-> 9
		RightBottomCorner //-> 3
	};

	struct LevelData
	{
		std::vector<std::pair<sf::Vector2i, BlockType>> blocks;
	};

	class LevelLoader
	{
	private:
		std::vector<LevelData>* levels;
	public:
		LevelLoader();
		~LevelLoader();

		unsigned long long GetLevelCount();
		LevelData& GetLevelData(unsigned long long index);
	private:
		static BlockType CharToBlockType(char symbol);
		std::vector<std::filesystem::path> GetAllFiles();
		void LoadLevelsFromFile();
	};
}