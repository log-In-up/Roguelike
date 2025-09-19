#pragma once
#include <memory>

#include "GameObject.h"
#include "HealthComponent.h"
#include "MovementComponent.h"

namespace Roguelike
{
class ActorMovementComponent : public GameEngine::MovementComponent
{
  public:
    explicit ActorMovementComponent(GameEngine::GameObject *gameObject, const float speed = 0.0F);

    void Update(float deltaTime) override;

  private:
    std::weak_ptr<HealthComponent> healtComponentPtr;
};
} // namespace Roguelike
