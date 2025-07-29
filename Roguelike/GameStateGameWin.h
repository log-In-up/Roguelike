#pragma once
#include <SFML/Graphics.hpp>

#include "GameStateData.h"

namespace Roguelike
{
	class Game;

	class GameStateGameWinData : public GameStateData
	{
	private:
		sf::Font* font;
		sf::RectangleShape* background;
		sf::Text* gameWinText;
		sf::Text* hintText;

		float timeSinceGameWin = 0.f;
	public:
		GameStateGameWinData();
		~GameStateGameWinData();
		void Draw(sf::RenderWindow& window) override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void Update(float timeDelta) override;
	};
}
