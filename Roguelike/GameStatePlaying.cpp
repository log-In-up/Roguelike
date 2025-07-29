#include <assert.h>
#include <sstream>

#include "Application.h"
#include "Game.h"
#include "GameStatePlaying.h"
#include "randomizer.h"
#include "Text.h"

namespace Roguelike
{
	GameStatePlayingData::GameStatePlayingData()
	{
		font = new sf::Font();

		inputHintText = new sf::Text();
		background = new sf::RectangleShape();
	}

	GameStatePlayingData::~GameStatePlayingData()
	{
		delete font;
		delete inputHintText;
		delete background;
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		window.draw(*background);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText->setPosition(viewSize.x - 10.f, 10.f);

		window.draw(*inputHintText);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().ExitGame();
			}
		}
	}

	void GameStatePlayingData::Init()
	{
		assert(font->loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));

		float x = (float)SETTINGS.SCREEN_WIDTH;
		float y = (float)SETTINGS.SCREEN_HEIGHT;

		background->setSize(sf::Vector2f(x, y));
		background->setPosition(x / 2, y / 2);
		background->setFillColor(sf::Color(0, 0, 0));

		SetTextData(*inputHintText, "TO BE DONE... Press Esc to exit to menu", *font, 24, sf::Color::White);
		inputHintText->setOrigin(GetTextOrigin(*inputHintText, { 1.f, 0.f }));
	}

	void GameStatePlayingData::LoadNextLevel()
	{
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
	}
}