#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace GameEngine
{
class RigidBodyComponent : public Component
{
  public:
    explicit RigidBodyComponent(GameObject *gameObject, const bool isKinematic = false);

    void Update(float deltaTime) override;

    bool GetKinematic() const;
    float GetAngleDamping() const;
    float GetAngleVelocity() const;
    float GetLinearDamping() const;
    Vector2Df GetLinearVelocity() const;
    void AddAngleVelocity(float angleOffset);
    void AddLinearVelocity(Vector2Df linearOffset);
    void SetAngleDamping(float newAngleDamping);
    void SetAngleVelocity(float newAngleVelocity);
    void SetKinematic(bool newIsKinematic);
    void SetLinearDamping(float newLinearDamping);
    void SetLinearVelocity(Vector2Df newLinearVelocity);

  private:
    TransformComponent *transform;

    Vector2Df linearVelocity = {0.0F, 0.0F};
    float angleVelocity = 0.0F;

    float linearDamping = 0.0F;
    float angleDamping = 0.0F;

    bool isKinematic = false;
};
} // namespace GameEngine
