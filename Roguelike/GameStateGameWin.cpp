#include <assert.h>
#include <sstream>

#include "Application.h"
#include "Game.h"
#include "GameStateGameWin.h"
#include "Text.h"

namespace Arkanoid
{
	GameStateGameWinData::GameStateGameWinData()
	{
		font = new sf::Font();
		background = new sf::RectangleShape();
		gameWinText = new sf::Text();
		hintText = new sf::Text();
	}

	GameStateGameWinData::~GameStateGameWinData()
	{
		delete font;
		delete background;
		delete gameWinText;
		delete hintText;
	}

	void GameStateGameWinData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background->setOrigin(0.f, 0.f);
		background->setSize(viewSize);
		window.draw(*background);

		gameWinText->setOrigin(GetTextOrigin(*gameWinText, { 0.5f, 1.f }));
		gameWinText->setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(*gameWinText);

		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 1.f }));
		hintText->setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(*hintText);
	}

	void GameStateGameWinData::GetStateData(Memento& memento)
	{
	}

	void GameStateGameWinData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				Application::Instance().GetGame().StartGame();
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().ExitGame();
			}
		}
	}

	void GameStateGameWinData::Init()
	{
		assert(font->loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		timeSinceGameWin = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200;
		background->setFillColor(backgroundColor);

		SetTextData(*gameWinText, "GAME WIN", *font, 48, sf::Color::Green);
		gameWinText->setStyle(sf::Text::Bold);

		SetTextData(*hintText, "Press Space to restart\nEsc to exit to main menu", *font, 24, sf::Color::White);
	}

	void GameStateGameWinData::SetStateData(Memento& memento)
	{
	}

	void GameStateGameWinData::Update(float timeDelta)
	{
		timeSinceGameWin += timeDelta;

		sf::Color GameWinTextColor = (int)timeSinceGameWin % 2 ? sf::Color::Green : sf::Color::Yellow;
		gameWinText->setFillColor(GameWinTextColor);
	}
}