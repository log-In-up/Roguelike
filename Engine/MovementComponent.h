#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace GameEngine
{
class MovementComponent : public Component
{
  public:
    explicit MovementComponent(GameObject *gameObject);
    MovementComponent(GameObject *gameObject, const float speed);

    void Update(float deltaTime) override;

    float GetAccelerationSquared() const;
    float GetSpeed() const;
    void SetSpeed(float newSpeed);

  private:
    TransformComponent *transform;

    float speed = 0.0F;
    Vector2Df previosPosition = {0.0F, 0.0F};
    Vector2Df acceleration = {0.0F, 0.0F};
};
} // namespace GameEngine
