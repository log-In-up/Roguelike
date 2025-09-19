#include "pch.h"

#include "AIInputComponent.h"

#include "GameObject.h"
#include "InputComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike
{
AIInputComponent::AIInputComponent(GameEngine::GameObject *gameObject) : InputComponent(gameObject)
{
}

void AIInputComponent::Update(float deltaTime)
{
}

GameEngine::Vector2Df AIInputComponent::GetDirection() const
{
    return {horizontalAxis, verticalAxis};
}

void AIInputComponent::SetDirection(const GameEngine::Vector2Df &newDirection)
{
    auto normalizedDirection = Normalized(newDirection);
    verticalAxis = normalizedDirection.y;
    horizontalAxis = normalizedDirection.x;
    if (normalizedDirection.GetLength() > 0.0F)
    {
        Emit();
    }
}
} // namespace Roguelike