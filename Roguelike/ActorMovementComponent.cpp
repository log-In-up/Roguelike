#include "ActorMovementComponent.h"

#include <memory>

#include "GameObject.h"
#include "HealthComponent.h"
#include "MovementComponent.h"

namespace Roguelike
{
ActorMovementComponent::ActorMovementComponent(GameEngine::GameObject *gameObject, const float speed)
    : MovementComponent(gameObject, speed)
{
    healtComponentPtr = gameObject->GetComponentSharedPtr<HealthComponent>();
}

void ActorMovementComponent::Update(float deltaTime)
{
    auto healthComponent = healtComponentPtr.lock();
    if (healthComponent && healthComponent->IsAlive())
    {
        MovementComponent::Update(deltaTime);
    }
}
} // namespace Roguelike