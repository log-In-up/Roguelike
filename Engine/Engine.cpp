#include "pch.h"
#include "Engine.h"
#include <iostream>
#include "GameWorld.h"
#include "RenderSystem.h"

namespace GameEngine
{
	Engine* Engine::Instance()
	{
		static Engine instance;
		return &instance;
	}

	Engine::Engine()
	{
		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);

		SetupLogger();
	}

	void Engine::Run()
	{
		sf::Clock gameClock;
		sf::Event event;

		LOG_INFO("Program was started!");

		while (RenderSystem::Instance()->GetMainWindow().isOpen())
		{
			sf::Time dt = gameClock.restart();
			float deltaTime = dt.asSeconds();

			while (RenderSystem::Instance()->GetMainWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					RenderSystem::Instance()->GetMainWindow().close();
				}
			}

			if (!RenderSystem::Instance()->GetMainWindow().isOpen())
			{
				break;
			}

			RenderSystem::Instance()->GetMainWindow().clear();

			GameWorld::Instance()->Update(deltaTime);
			GameWorld::Instance()->FixedUpdate(deltaTime);
			GameWorld::Instance()->Render(RenderSystem::Instance()->GetMainWindow());
			GameWorld::Instance()->LateUpdate();

			RenderSystem::Instance()->GetMainWindow().display();
		}
	}

	void Engine::SetupLogger()
	{
		auto logger = std::make_shared<Logger>();
		logger->AddSink(std::make_shared<ConsoleSink>());
		logger->AddSink(std::make_shared<FileSink>("Log.txt"));

		LoggerRegistry::GetInstance().RegisterLogger("global", logger);
		LoggerRegistry::GetInstance().SetDefaultLogger(logger);
	}
}