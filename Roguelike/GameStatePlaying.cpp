#include <assert.h>
#include <sstream>
#include <ResourceSystem.h>

#include "Application.h"
#include "Game.h"
#include "GameStatePlaying.h"
#include "randomizer.h"
#include "Text.h"
#include "DeveloperLevel.h"

namespace Roguelike
{
	GameStatePlayingData::GameStatePlayingData()
	{
		font = new sf::Font();

		level = new DeveloperLevel();
	}

	GameStatePlayingData::~GameStatePlayingData()
	{
		delete font;

		level->Stop();
		delete level;
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				level->Stop();
				Application::Instance().GetGame().ExitGame();
			}
		}
	}

	void GameStatePlayingData::Init()
	{
		assert(font->loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));

		float x = (float)SETTINGS.SCREEN_WIDTH;
		float y = (float)SETTINGS.SCREEN_HEIGHT;

		ResourceSystem::Instance()->LoadTextureMap("player", "Resources/TextureMaps/Player.png", { 48, 63 }, 4, false);
		ResourceSystem::Instance()->LoadTextureMap("level_floors", "Resources/TextureMaps/Floor.png", { 16, 16 }, 49, false);
		ResourceSystem::Instance()->LoadTextureMap("level_walls", "Resources/TextureMaps/Wall.png", { 16, 16 }, 48, false);

		ResourceSystem::Instance()->LoadSound("music", "Resources/Sounds/AppleEat.wav");

		level->Start();
	}

	void GameStatePlayingData::LoadNextLevel()
	{
		level->Restart();
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
	}
}