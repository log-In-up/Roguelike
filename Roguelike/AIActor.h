#pragma once
#include "AIChaseTargetComponent.h"
#include "Actor.h"
#include "PerceptionComponent.h"
#include "Vector.h"

namespace Roguelike
{
class AIActor : public Actor
{
  public:
    friend class AIActorManagerSystem;

    struct Parameters
    {
        Actor::Parameters baseActorParameters;
        AIChaseTargetComponent::Parameters chaseTargetParameters = {0.0F, 0.0F};
        PerceptionComponent::Parameters perceptionParameters = PerceptionComponent::defaultParameters;
    };

  private:
    explicit AIActor(const Parameters &parameters, const GameEngine::Vector2Df &position = {0.0F, 0.0F});
};
} // namespace Roguelike