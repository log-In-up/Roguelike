#include <cstdlib>
#include <RenderSystem.h>
#include <GameWorld.h>
//#include <Logger.h>

#include "Application.h"
#include <Engine.h>

namespace Roguelike
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	void Application::Run()
	{
		GameEngine::Engine::Instance()->SetupLogger();

		sf::Clock gameClock;
		sf::Event event;

		//LOG_INFO("Program was started!");

		GameEngine::RenderSystem::Instance()->SetMainWindow(window);

		while (GameEngine::RenderSystem::Instance()->GetMainWindow().isOpen())
		{
			sf::Time dt = gameClock.restart();
			float deltaTime = dt.asSeconds();

			game->HandleWindowEvents(*window);
			while (GameEngine::RenderSystem::Instance()->GetMainWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					GameEngine::RenderSystem::Instance()->GetMainWindow().close();
				}
			}

			if (!game->Update(deltaTime))
			{
				GameEngine::RenderSystem::Instance()->GetMainWindow().close();
			}

			if (!GameEngine::RenderSystem::Instance()->GetMainWindow().isOpen())
			{
				break;
			}

			GameEngine::RenderSystem::Instance()->GetMainWindow().clear();

			GameEngine::GameWorld::Instance()->Update(deltaTime);
			GameEngine::GameWorld::Instance()->FixedUpdate(deltaTime);

			GameEngine::GameWorld::Instance()->Render(*window);
			game->Draw(*window);
			GameEngine::GameWorld::Instance()->LateUpdate();

			GameEngine::RenderSystem::Instance()->GetMainWindow().display();
		}
	}

	Application::Application()
	{
		window = new sf::RenderWindow(sf::VideoMode(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT), SETTINGS.GAME_NAME);
		game = new Game();

		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);
	}

	Application::~Application()
	{
		delete window;
		delete game;
	}
}