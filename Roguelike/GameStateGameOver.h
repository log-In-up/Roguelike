#pragma once
#include <SFML/Graphics.hpp>

#include "GameStateData.h"

namespace Arkanoid
{
	class Game;

	class GameStateGameOverData : public GameStateData
	{
	private:
		sf::Font* font;
		sf::RectangleShape* background;
		sf::Text* gameOverText;
		sf::Text* hintText;
		std::vector<sf::Text>* recordsTableTexts;

		float timeSinceGameOver = 0.f;
	public:
		GameStateGameOverData();
		~GameStateGameOverData();
		void Draw(sf::RenderWindow& window) override;
		void GetStateData(Memento& memento) override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void SetStateData(Memento& memento) override;
		void Update(float timeDelta) override;
	};
}
