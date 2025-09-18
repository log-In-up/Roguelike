#include "BlockComponent.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "RenderSystem.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike
{
const BlockComponent::Parameters BlockComponent::defaultParameters = {.damageReduction = 1.0F,
                                                                      .speedCoefficient = 0.9F,
                                                                      .iconCenterOffset = {0.0F, 0.0F},
                                                                      .iconRadius = 4.0F,
                                                                      .iconColor = sf::Color::Green};

BlockComponent::BlockComponent(GameEngine::GameObject *gameObject, const Parameters &parameters, const int layer)
    : Component(gameObject), IRenderable(layer), damageReduction(parameters.damageReduction),
      speedCoefficient(parameters.speedCoefficient), iconCenterOffset(parameters.iconCenterOffset),
      iconRadius(parameters.iconRadius), iconColor(parameters.iconColor) {};

void BlockComponent::Render()
{
    if (isBlocking)
    {
        sf::CircleShape icon(iconRadius);
        icon.setFillColor(iconColor);
        auto *transform = gameObject->GetComponent<GameEngine::TransformComponent>();
        auto position = transform->GetWorldPosition() + iconCenterOffset;
        icon.setPosition(Convert<sf::Vector2f>(position));
        GameEngine::RenderSystem::Instance()->Render(icon, layer);
    }
}

// NOLINTBEGIN(misc-unused-parameters) : inhereted method with parameter
void BlockComponent::Update(float deltaTime)
{
    if (const auto *input = gameObject->GetComponent<GameEngine::InputComponent>())
    {
        auto isBlockingInput = input->GetBlock();
        if (isBlocking && !isBlockingInput)
        {
            if (auto *movementComponent = gameObject->GetComponent<GameEngine::MovementComponent>())
            {
                auto newSpeed = 1.0F / speedCoefficient * movementComponent->GetSpeed();
                movementComponent->SetSpeed(newSpeed);
            }
            isBlocking = isBlockingInput;
        }
        else if (!isBlocking && isBlockingInput)
        {
            if (auto *movementComponent = gameObject->GetComponent<GameEngine::MovementComponent>())
            {
                auto newSpeed = speedCoefficient * movementComponent->GetSpeed();
                movementComponent->SetSpeed(newSpeed);
            }
            isBlocking = isBlockingInput;
        }
    }
}
// NOLINTEND(misc-unused-parameters)

bool BlockComponent::GetIsBlocking() const
{
    return isBlocking;
};

float BlockComponent::ApplyDamage(const float damage) const
{
    if (!isBlocking)
    {
        return damage;
    }
    return damage * (1.0F - damageReduction);
}
} // namespace Roguelike