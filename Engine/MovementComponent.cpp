#include "pch.h"

#include "MovementComponent.h"

#include "Component.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "SpriteAnimationComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace GameEngine
{
MovementComponent::MovementComponent(GameObject *gameObject) : Component(gameObject)
{
    transform = gameObject->GetComponent<TransformComponent>();
}

MovementComponent::MovementComponent(GameObject *gameObject, const float speed) : Component(gameObject)
{
    transform = gameObject->GetComponent<TransformComponent>();
    MovementComponent::speed = speed;
}

void MovementComponent::Update(float deltaTime)
{
    if (auto *input = gameObject->GetComponent<InputComponent>())
    {
        const Vector2Df direction = Vector2Df{input->GetHorizontalAxis(), input->GetVerticalAxis()};

        transform->MoveBy(speed * deltaTime * direction);
        acceleration = transform->GetWorldPosition() - previosPosition;
        previosPosition = transform->GetWorldPosition();
        if (auto *animationComponent = gameObject->GetComponent<SpriteAnimationComponent>())
        {
            if (direction.GetLength() > 0.0F)
            {
                animationComponent->StartAnimation("Walk");
            }
            else
            {
                animationComponent->StartAnimation("Idle");
            }
        }
    }
}

float MovementComponent::GetAccelerationSquared() const
{
    const Vector2Df squaredAcceleration = acceleration * acceleration;
    return squaredAcceleration.x + squaredAcceleration.y;
}

float MovementComponent::GetSpeed() const
{
    return speed;
}

void MovementComponent::SetSpeed(float newSpeed)
{
    speed = newSpeed;
}
} // namespace GameEngine