#include "AIChaseTargetComponent.h"

#include "AIBlackboard.h"
#include "AIInputComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "Logger.h"
#include "TransformComponent.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike
{
AIChaseTargetComponent::AIChaseTargetComponent(GameEngine::GameObject *gameObject, const Parameters &parameters)
    : Component(gameObject), minumumChaseRadius(parameters.minumumChaseRadius),
      maximumChaseRadius(parameters.maximumChaseRadius)
{
}

// NOLINTBEGIN(misc-unused-parameters) : overrided virtual method
void AIChaseTargetComponent::Update(float deltaTime)
{
    auto *blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (blackBoard != nullptr)
    {
        GameEngine::Vector2Df movingDirection;

        bool isTargetVisible = false;
        GameEngine::GameObject *target = nullptr;
        if (blackBoard->Get("isTargetVisible", isTargetVisible) && isTargetVisible &&
            blackBoard->Get("lastTarget", target) && target != nullptr)
        {
            auto betweenVector = target->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition() -
                                 gameObject->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition();

            auto distance = betweenVector.GetLength();
            if (InRange(distance, minumumChaseRadius, maximumChaseRadius))
            {
                movingDirection = betweenVector;
            }
        }
        auto *inputComponent = gameObject->GetComponent<AIInputComponent>();
        inputComponent->SetDirection(movingDirection);
    }
    else
    {
        LOG_ERROR("AIBlackboard requried for AIChaseComponent");
    }
}
// NOLINTEND(misc-unused-parameters) : overrided method

void AIChaseTargetComponent::SetMaximumChaseRadius(float newMaximumRadius)
{
    maximumChaseRadius = newMaximumRadius;
}

void AIChaseTargetComponent::SetMinimumChaseRadius(float newMinimuRadius)
{
    minumumChaseRadius = newMinimuRadius;
}
} // namespace Roguelike