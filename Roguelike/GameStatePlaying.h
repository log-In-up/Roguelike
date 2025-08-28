#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "GameStateData.h"
#include "IObserver.h"
#include "DeveloperLevel.h"

namespace Roguelike
{
	class Game;

	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>
	{
	private:
		sf::Font* font;

		DeveloperLevel* level;
	public:
		GameStatePlayingData();
		~GameStatePlayingData();
		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;
		void Update(float timeDelta) override;
	};
}
