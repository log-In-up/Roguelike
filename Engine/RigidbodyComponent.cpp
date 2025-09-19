#include "pch.h"

#include "RigidBodyComponent.h"

#include <cmath>

#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace GameEngine
{
RigidBodyComponent::RigidBodyComponent(GameObject *gameObject, const bool isKinematic)
    : Component(gameObject), isKinematic(isKinematic)
{
    transform = gameObject->GetComponent<TransformComponent>();
}

void RigidBodyComponent::Update(float deltaTime)
{
    transform->MoveBy(linearVelocity);
    transform->RotateBy(angleVelocity);

    linearVelocity *= (1.0F - (linearDamping * deltaTime));
    angleVelocity *= (1.0F - (angleDamping * deltaTime));

    constexpr float minimalVelocity = 0.001F;

    if (fabs(linearVelocity.x) < minimalVelocity)
    {
        linearVelocity.x = 0.0F;
    }

    if (fabs(linearVelocity.y) < minimalVelocity)
    {
        linearVelocity.y = 0.0F;
    }

    if (fabs(angleVelocity) < minimalVelocity)
    {
        angleVelocity = 0.0F;
    }
}

bool RigidBodyComponent::GetKinematic() const
{
    return isKinematic;
}

float RigidBodyComponent::GetAngleDamping() const
{
    return angleDamping;
}

float RigidBodyComponent::GetAngleVelocity() const
{
    return angleVelocity;
}

float RigidBodyComponent::GetLinearDamping() const
{
    return linearDamping;
}

Vector2Df RigidBodyComponent::GetLinearVelocity() const
{
    return linearVelocity;
}

void RigidBodyComponent::AddAngleVelocity(float angleOffset)
{
    angleVelocity += angleOffset;
}

void RigidBodyComponent::AddLinearVelocity(Vector2Df linearOffset)
{
    linearVelocity += linearOffset;
}

void RigidBodyComponent::SetAngleDamping(float newAngleDamping)
{
    angleDamping = newAngleDamping;
}

void RigidBodyComponent::SetAngleVelocity(float newAngleVelocity)
{
    angleVelocity = newAngleVelocity;
}

void RigidBodyComponent::SetKinematic(bool newIsKinematic)
{
    isKinematic = newIsKinematic;
}

void RigidBodyComponent::SetLinearDamping(float newLinearDamping)
{
    linearDamping = newLinearDamping;
}

void RigidBodyComponent::SetLinearVelocity(Vector2Df newLinearVelocity)
{
    linearVelocity = newLinearVelocity;
}
} // namespace GameEngine