#include "SpriteOpaqueComponent.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "GameObject.h"
#include "IRenderable.h"
#include "Logger.h"
#include "OpaqueComponent.h"
#include "PerceptionSystem.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

namespace Roguelike
{
constexpr float outlineThickness = -2.0F;
SpriteOpaqueComponent::SpriteOpaqueComponent(GameEngine::GameObject *gameObject, const int layer)
    : OpaqueComponent(gameObject), IRenderable(layer), sprite(nullptr)
{
    auto *spriteRenderer = gameObject->GetComponent<GameEngine::SpriteRendererComponent>();
    if (spriteRenderer == nullptr)
    {
        LOG_ERROR("SpriteRendererComponent required to SpriteOpaqueComponent.");
        gameObject->RemoveComponent(this);
        return;
    }

    sprite = spriteRenderer->GetSprite();
    PerceptionSystem::Instance()->RegisterOpaqueComponent(this);
}

SpriteOpaqueComponent::~SpriteOpaqueComponent()
{
    PerceptionSystem::Instance()->UnregisterOpaqueComponent(this);
}

// NOLINTEND(misc-unused-parameters)
void SpriteOpaqueComponent::Render()
{
    sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(bounds.left, bounds.top);
    rectangle.setOutlineColor(sf::Color::Cyan);
    rectangle.setOutlineThickness(outlineThickness);
    GameEngine::RenderSystem::Instance()->Render(rectangle, layer);
}

// NOLINTBEGIN(misc-unused-parameters) : overrided method with parameter
void SpriteOpaqueComponent::Update(float deltaTime)
{
    bounds = sprite->getGlobalBounds();
}
} // namespace Roguelike