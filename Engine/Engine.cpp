#include "pch.h"

#include "Engine.h"

#include <cstdlib>
#include <ctime>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "EventSystem.h"
#include "GameWorld.h"
#include "Logger.h"
#include "RenderSystem.h"

namespace GameEngine
{
Engine::Engine()
{
    const unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
}

Engine *Engine::Instance()
{
    static Engine instance;
    return &instance;
}

void Engine::Run()
{
    LOG_INFO("Engine runned");
    sf::Clock gameClock;

    while (RenderSystem::Instance()->GetMainWindow().isOpen())
    {
        const sf::Time timeElapsed = gameClock.restart();
        const float deltaTime = timeElapsed.asSeconds();

        EventSystem::Instance()->UpdateSfEvents();

        auto closeEvent = EventSystem::Instance()->GetSfEvents(sf::Event::Closed);
        if (closeEvent.first != closeEvent.second)
        {
            GameWorld::Instance()->ClearImmediate();
            break;
        }

        RenderSystem::Instance()->Clear();

        GameWorld::Instance()->Update(deltaTime);
        GameWorld::Instance()->FixedUpdate(deltaTime);
        GameWorld::Instance()->Render();
        GameWorld::Instance()->LateUpdate();

        RenderSystem::Instance()->Display();
    }

    LOG_INFO("Engine stopped");
}
} // namespace GameEngine