#include "ActorSpriteDirectionComponent.h"

#include <memory>

#include "GameObject.h"
#include "HealthComponent.h"
#include "SpriteDirectionComponent.h"

namespace Roguelike
{
ActorSpriteDirectionComponent::ActorSpriteDirectionComponent(GameEngine::GameObject *gameObject)
    : SpriteDirectionComponent(gameObject)
{
    healthComponentPtr = gameObject->GetComponentSharedPtr<HealthComponent>();
}

void ActorSpriteDirectionComponent::Update(float deltaTime)
{
    auto healthComponent = healthComponentPtr.lock();
    if (healthComponent && healthComponent->IsAlive())
    {
        SpriteDirectionComponent::Update(deltaTime);
    }
}
} // namespace Roguelike