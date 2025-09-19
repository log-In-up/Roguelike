#include "pch.h"

#include "KeyboardInputComponent.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "EventSystem.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "Logger.h"
#include "RenderSystem.h"
#include "Settings.h"

namespace Roguelike
{
KeyboardInputComponent::KeyboardInputComponent(GameEngine::GameObject *gameObject) : InputComponent(gameObject)
{
}
// NOLINTBEGIN(misc-unused-parameters) : inhereted method with parameter
void KeyboardInputComponent::Update(float deltaTime)
{
    verticalAxis = 0.0F;
    horizontalAxis = 0.0F;
    attack = false;
    block = false;
    levelTransfer = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (logInput)
        {
            LOG_INFO("Forward input");
        }
        verticalAxis += 1.0F;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (logInput)
        {
            LOG_INFO("Backward input");
        }
        verticalAxis -= 1.0F;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (logInput)
        {
            LOG_INFO("Right input");
        }
        horizontalAxis += 1.0F;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (logInput)
        {
            LOG_INFO("Left input");
        }
        horizontalAxis -= 1.0F;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (logInput)
        {
            LOG_INFO("Block input");
        }
        block = true;
    }
    auto keyEvents = GameEngine::EventSystem::Instance()->GetSfEvents(sf::Event::KeyPressed);
    for (auto event = keyEvents.first; event != keyEvents.second; event++)
    {
        if (event->second.key.code == sf::Keyboard::Space)
        {
            if (logInput)
            {
                LOG_INFO("Attack input");
            }
            attack = true;
            Emit();
        }
        if (event->second.key.code == sf::Keyboard::T)
        {
            if (logInput)
            {
                LOG_INFO("Level transfer input");
            }
            levelTransfer = true;
            Emit();
        }
        if (event->second.key.code == sf::Keyboard::F11)
        {
            if (logInput)
            {
                LOG_INFO("Turning debug render level on/off");
            }
            auto *renderSystem = GameEngine::RenderSystem::Instance();
            auto layers = renderSystem->GetActiveLayers();
            constexpr int debugLayer = static_cast<int>(Settings::RenderLayers::Debug);
            layers.SetLayerValue(debugLayer, !layers.GetLayerValue(debugLayer));
            renderSystem->SetActiveLayers(layers);
        }
        if (event->second.key.code == sf::Keyboard::F10)
        {
            if (logInput)
            {
                LOG_INFO("Turning input loggin off");
            }
            else
            {
                LOG_INFO("Turning input loggin on");
            }
            logInput = !logInput;
        }
    }
}
// NOLINTEND(misc-unused-parameters)
} // namespace Roguelike