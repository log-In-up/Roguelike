#pragma once
#include <SFML/Graphics.hpp>

#include "GameStateData.h"
#include "Menu.h"

namespace Arkanoid
{
	class Game;

	class GameStatePauseMenuData : public GameStateData
	{
	private:
		Menu* menu;
		sf::Font* font;
		sf::RectangleShape* background;
		sf::Text* titleText;
	public:
		GameStatePauseMenuData();
		~GameStatePauseMenuData();
		void Draw(sf::RenderWindow& window) override;
		void GetStateData(Memento& memento) override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Init() override;
		void SetStateData(Memento& memento) override;
		void Update(float timeDelta) override;
	};
}
