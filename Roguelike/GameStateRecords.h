#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "GameStateData.h"

namespace Arkanoid
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
		void GetStateData(Memento& memento) override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void SetStateData(Memento& memento) override;
		void Update(float timeDelta) override;
	};
}
