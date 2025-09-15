#include <cassert>
#include <fstream>

#include "LevelLoader.h"
#include "GameSettings.h"

namespace Roguelike
{
	LevelLoader::LevelLoader()
	{
		levels = new std::vector<LevelData>();

		LoadLevelsFromFile();
	}

	LevelLoader::~LevelLoader()
	{
		delete levels;
	}

	unsigned long long LevelLoader::GetLevelCount()
	{
		return levels->size();
	}

	LevelData& LevelLoader::GetLevelData(unsigned long long index)
	{
		return levels->at(index);
	}

	BlockType LevelLoader::CharToBlockType(char symbol)
	{
		BlockType blockType;
		switch (symbol)
		{
		case 'O':
			blockType = BlockType::BossSpawn;
			break;
		case 'E':
			blockType = BlockType::Exit;
			break;
		case 'F':
			blockType = BlockType::Floor;
			break;
		case 'P':
			blockType = BlockType::PlayerSpawn;
			break;
		case 'B':
			blockType = BlockType::BottomWall;
			break;
		case 'L':
			blockType = BlockType::LeftWall;
			break;
		case 'R':
			blockType = BlockType::RightWall;
			break;
		case 'T':
			blockType = BlockType::TopWall;
			break;
		case '1':
			blockType = BlockType::LeftBottomCorner;
			break;
		case '3':
			blockType = BlockType::RightBottomCorner;
			break;
		case '7':
			blockType = BlockType::LeftTopCorner;
			break;
		case '9':
			blockType = BlockType::RightTopCorner;
			break;
		default:
			assert(false);
			break;
		}
		return blockType;
	}

	std::vector<std::filesystem::path> LevelLoader::GetAllFiles()
	{
		std::vector<std::filesystem::path> paths;

		for (auto& entry : std::filesystem::recursive_directory_iterator(SETTINGS.LEVELS_CONFIG_PATH))
		{
			if (entry.path().extension() == EXTENSION)
			{
				paths.emplace_back(entry.path());
			}
		}

		return paths;
	}

	void LevelLoader::LoadLevelsFromFile()
	{
		std::vector<std::filesystem::path> paths = GetAllFiles();

		for (std::filesystem::path& path : paths)
		{
			std::ifstream file(path);
			std::string line;
			int y = 0;

			LevelData data;
			while (getline(file, line))
			{
				int x = 0;
				for (char symbol : line)
				{
					if (symbol != ' ')
					{
						BlockType block = CharToBlockType(symbol);
						sf::Vector2i position{ x, y };

						data.blocks.emplace_back(std::make_pair(position, block));
					}
					++x;
				}
				++y;
			}

			levels->push_back(data);

			file.close();
		}
	}
}