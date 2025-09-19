#pragma once
#include "Component.h"
#include "GameObject.h"

namespace Roguelike
{
class AIChaseTargetComponent : public GameEngine::Component
{
  public:
    struct Parameters
    {
        float minumumChaseRadius = 0.0F;
        float maximumChaseRadius = 0.0F;
    };
    explicit AIChaseTargetComponent(GameEngine::GameObject *gameObject, const Parameters &parameters = {0.0F, 0.0F});

    void Update(float deltaTime) override;

    void SetMaximumChaseRadius(float newMaximumRadius);
    void SetMinimumChaseRadius(float newMinimuRadius);

  private:
    float minumumChaseRadius = 0.0F;
    float maximumChaseRadius = 0.0F;
};
} // namespace Roguelike
