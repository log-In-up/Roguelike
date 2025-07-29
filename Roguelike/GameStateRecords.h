#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "GameStateData.h"

namespace Roguelike
{
	class Game;

	class GameStateRecordsData : public GameStateData
	{
	private:
		sf::Font* font;
		sf::Text* hintText;
		sf::Text* titleText;
		std::vector<sf::Text>* tableTexts;
	public:
		GameStateRecordsData();
		~GameStateRecordsData();
		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void Update(float timeDelta) override;
	};
}
