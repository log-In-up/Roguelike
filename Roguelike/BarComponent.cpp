#include "BarComponent.h"

#include <cmath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.h"
#include "GameObject.h"
#include "IRenderable.h"
#include "Logger.h"
#include "RenderSystem.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike
{
const BarComponent::Parameters BarComponent::defaultBarParameters{.centerOffset = {0.0F, 0.0F},
                                                                  .barSize = {1.0F, 0.0F},
                                                                  .barColor = sf::Color::White,
                                                                  .borderSize = 0.0F,
                                                                  .maxAmount = 1.0F};

BarComponent::BarComponent(GameEngine::GameObject *gameObject, const Parameters &parameters, const int renderLayer)
    : Component(gameObject), IRenderable(renderLayer), centerOffset(parameters.centerOffset),
      barSize(parameters.barSize), barColor(parameters.barColor), maxAmount(parameters.maxAmount),
      currentAmount(parameters.maxAmount), borderSize(parameters.borderSize)
{
}

void BarComponent::Render()
{
    if (maxAmount <= 0.0F)
    {
        LOG_WARN("Bars maxAmount should be positive");
        return;
    }

    const auto &objectPosition = gameObject->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition();
    auto barTopLeft = objectPosition + centerOffset - Half(barSize);
    const GameEngine::Vector2Df filledBarSize = {barSize.x * currentAmount / maxAmount, barSize.y};

    if (abs(borderSize) > 0.0F)
    {
        sf::RectangleShape borderShape(Convert<sf::Vector2f>(barSize));
        borderShape.setFillColor(sf::Color::Transparent);
        borderShape.setOutlineColor(barColor);
        borderShape.setOutlineThickness(borderSize);
        borderShape.setPosition(Convert<sf::Vector2f>(barTopLeft));
        GameEngine::RenderSystem::Instance()->Render(borderShape, layer);
    }

    sf::RectangleShape barShape(Convert<sf::Vector2f>(filledBarSize));
    barShape.setFillColor(barColor);
    barShape.setPosition(Convert<sf::Vector2f>(barTopLeft));
    GameEngine::RenderSystem::Instance()->Render(barShape, layer);
}

float BarComponent::GetBorderSize() const
{
    return borderSize;
}

float BarComponent::GetCurrentAmount() const
{
    return currentAmount;
}

float BarComponent::GetMaxAmount() const
{
    return maxAmount;
}

GameEngine::Vector2Df BarComponent::GetBarSize() const
{
    return barSize;
}

GameEngine::Vector2Df BarComponent::GetCenterOffset() const
{
    return centerOffset;
}

sf::Color BarComponent::GetBarColor() const
{
    return barColor;
}

void BarComponent::SetBarColor(const sf::Color newBarColor)
{
    barColor = newBarColor;
}

void BarComponent::SetBarSize(const GameEngine::Vector2Df &newBarSize)
{
    barSize = newBarSize;
}

void BarComponent::SetBorderSize(const float newBorderSize)
{
    borderSize = newBorderSize;
}

void BarComponent::SetCenterOffset(const GameEngine::Vector2Df &newCenterOffset)
{
    centerOffset = newCenterOffset;
}

void BarComponent::SetCurrentAmount(const float newCurrentAmount)
{
    currentAmount = newCurrentAmount;
}

void BarComponent::SetMaxAmount(const float newMaxAmount)
{
    if (newMaxAmount <= 0.0F)
    {
        LOG_WARN("Bars maxAmount should be positive");
        return;
    }
    maxAmount = newMaxAmount;
}
} // namespace Roguelike