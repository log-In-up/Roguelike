#include "pch.h"

#include "InputComponent.h"

#include "Component.h"
#include "GameObject.h"

namespace GameEngine
{
InputComponent::InputComponent(GameObject *gameObject) : Component(gameObject)
{
}

bool InputComponent::GetAttack() const
{
    return attack;
}

bool InputComponent::GetBlock() const
{
    return block;
}

bool InputComponent::GetLevelTransfer() const
{
    return levelTransfer;
}

float InputComponent::GetVerticalAxis() const
{
    return verticalAxis;
}

float InputComponent::GetHorizontalAxis() const
{
    return horizontalAxis;
}
} // namespace GameEngine