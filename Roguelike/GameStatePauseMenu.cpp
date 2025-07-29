#include <assert.h>

#include "Application.h"
#include "Game.h"
#include "GameStatePauseMenu.h"
#include "Text.h"

namespace Arkanoid
{
	GameStatePauseMenuData::GameStatePauseMenuData()
	{
		menu = new Menu();
		font = new sf::Font();
		background = new sf::RectangleShape();
		titleText = new sf::Text();
	}

	GameStatePauseMenuData::~GameStatePauseMenuData()
	{
		delete menu;
		delete font;
		delete background;
		delete titleText;
	}

	void GameStatePauseMenuData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		background->setSize(viewSize);
		window.draw(*background);

		titleText->setOrigin(GetTextOrigin(*titleText, { 0.5f, 0.f }));
		titleText->setPosition(viewSize.x / 2.f, 100);
		window.draw(*titleText);

		menu->Draw(window, window.getView().getCenter(), { 0.5f, 0.f });
	}

	void GameStatePauseMenuData::GetStateData(Memento& memento)
	{
	}

	void GameStatePauseMenuData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				menu->PressOnSelectedItem();
			}

			Orientation orientation = menu->GetCurrentContext().childrenOrientation;
			if (event.key.code == sf::Keyboard::Up)
			{
				menu->SwitchToPreviousMenuItem();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				menu->SwitchToNextMenuItem();
			}
		}
	}

	void GameStatePauseMenuData::Init()
	{
		assert(font->loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		background->setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black

		SetTextData(*titleText, "Pause", *font, 48, sf::Color::Red);

		MenuItem resumeItem;
		SetTextData(resumeItem.text, "Return to game", *font, 24);
		resumeItem.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().PopState();
			};

		MenuItem exitItem;
		SetTextData(exitItem.text, "Exit to main menu", *font, 24);
		exitItem.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().ExitGame();
			};

		MenuItem pauseMenu;
		pauseMenu.childrenOrientation = Orientation::Vertical;
		pauseMenu.childrenAlignment = Alignment::Middle;
		pauseMenu.childrens.push_back(resumeItem);
		pauseMenu.childrens.push_back(exitItem);

		menu->Init(pauseMenu);
	}

	void GameStatePauseMenuData::SetStateData(Memento& memento)
	{
	}

	void GameStatePauseMenuData::Update(float timeDelta)
	{
	}
}