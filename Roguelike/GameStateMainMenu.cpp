#include <assert.h>

#include "Application.h"
#include "Game.h"
#include "GameStateMainMenu.h"
#include "Text.h"

namespace Arkanoid
{
	GameStateMainMenuData::GameStateMainMenuData()
	{
		font = new sf::Font();
		menu = new Menu();
	}

	GameStateMainMenuData::~GameStateMainMenuData()
	{
		delete font;
		delete menu;
	}

	void GameStateMainMenuData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &menu->GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		menu->Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}

	void GameStateMainMenuData::GetStateData(Memento& memento)
	{
	}

	void GameStateMainMenuData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				menu->GoBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				menu->PressOnSelectedItem();
			}

			Orientation orientation = menu->GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu->SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu->SwitchToNextMenuItem();
			}
		}
	}

	void GameStateMainMenuData::Init()
	{
		assert(font->loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		MenuItem startGame;
		SetTextData(startGame.text, "Start Game", *font, 24);
		startGame.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().StartGame();
			};

		const bool isInfiniteApples = Application::Instance().GetGame().IsEnableOptions(GameOptions::InfiniteApples);
		MenuItem optionsInfiniteApplesItem;
		SetTextData(optionsInfiniteApplesItem.text,
			"Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"),
			*font, 24);
		optionsInfiniteApplesItem.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newOptionValue = !game.IsEnableOptions(GameOptions::InfiniteApples);
				game.SetOption(GameOptions::InfiniteApples, newOptionValue);
				item.text.setString("Infinite Apples: " + std::string(newOptionValue ? "On" : "Off"));
			};

		const bool isWithAcceleration = Application::Instance().GetGame().IsEnableOptions(GameOptions::WithAcceleration);
		MenuItem optionsWithAccelerationItem;
		SetTextData(optionsWithAccelerationItem.text,
			"With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"),
			*font, 24);
		optionsWithAccelerationItem.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newOptionValue = !game.IsEnableOptions(GameOptions::WithAcceleration);
				game.SetOption(GameOptions::WithAcceleration, newOptionValue);
				item.text.setString("With Acceleration: " + std::string(newOptionValue ? "On" : "Off"));
			};

		MenuItem options;
		SetTextData(options.text, "Options", *font, 24);
		SetTextData(options.hintText, "Options", *font, 48, sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;
		options.childrens.push_back(optionsInfiniteApplesItem);
		options.childrens.push_back(optionsWithAccelerationItem);

		MenuItem recordsItem;
		SetTextData(recordsItem.text, "Records", *font, 24);
		recordsItem.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().ShowRecords();
			};

		MenuItem yesItem;
		SetTextData(yesItem.text, "Yes", *font, 24);
		yesItem.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().QuitGame();
			};

		MenuItem noItem;
		SetTextData(noItem.text, "No", *font, 24);
		noItem.onPressCallback = [this](MenuItem&)
			{
				menu->GoBack();
			};

		MenuItem exitGameItem;
		SetTextData(exitGameItem.text, "Exit Game", *font, 24);
		SetTextData(exitGameItem.hintText, "Are you sure?", *font, 48, sf::Color::Red);
		exitGameItem.childrenOrientation = Orientation::Horizontal;
		exitGameItem.childrenAlignment = Alignment::Middle;
		exitGameItem.childrenSpacing = 10.f;
		exitGameItem.childrens.push_back(yesItem);
		exitGameItem.childrens.push_back(noItem);

		MenuItem mainMenu;
		SetTextData(mainMenu.hintText, "Arkanoid Game", *font, 48, sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(recordsItem);
		mainMenu.childrens.push_back(exitGameItem);

		menu->Init(mainMenu);
	}

	void GameStateMainMenuData::SetStateData(Memento& memento)
	{
	}

	void GameStateMainMenuData::Update(float timeDelta)
	{
	}
}