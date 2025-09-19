#pragma once
#include <memory>

#include "GameObject.h"
#include "HealthComponent.h"
#include "SpriteDirectionComponent.h"
namespace Roguelike
{
class ActorSpriteDirectionComponent : public GameEngine::SpriteDirectionComponent
{
  public:
    explicit ActorSpriteDirectionComponent(GameEngine::GameObject *gameObject);

    void Update(float deltaTime) override;

  private:
    std::weak_ptr<HealthComponent> healthComponentPtr;
};
} // namespace Roguelike
