#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Ball.h"
#include "BlockFactory.h"
#include "Bonus.h"
#include "GameStateData.h"
#include "IObserver.h"
#include "LevelLoader.h"
#include "Platform.h"
#include "BonusObject.h"

namespace Arkanoid
{
	class Game;
	class Block;
	class BlockFactory;

	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>
	{
	private:
		sf::Texture* appleTexture;
		sf::Texture* rockTexture;
		sf::Font* font;
		sf::SoundBuffer* eatAppleSoundBuffer;
		sf::SoundBuffer* gameOverSoundBuffer;
		sf::SoundBuffer* bonusSoundBuffer;

		std::vector<std::shared_ptr<GameObject>>* gameObjects;
		std::vector<std::shared_ptr<Block>>* blocks;
		std::vector<std::shared_ptr<BonusObject>>* bonusObjects;

		sf::Text* scoreText;
		sf::Text* inputHintText;
		sf::RectangleShape* background;

		sf::Sound* gameOverSound;
		sf::Sound* bonusSound;

		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>>* factories;
		LevelLoader* levelLoder;

		std::map<BonusType, Bonus>* bonuses;

		int breackableBlocksCount = 0;
		int currentLevel = 0;

	public:
		GameStatePlayingData();
		~GameStatePlayingData();
		void Draw(sf::RenderWindow& window) override;
		void GetStateData(Memento& memento) override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;
		void SetStateData(Memento& memento) override;
		void Update(float timeDelta) override;
	private:
		void CreateBlocks();
		void GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY);
	};
}
