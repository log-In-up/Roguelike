#include "pch.h"

#include "TransformComponent.h"

#include <cmath>
#include <iostream>
#include <numbers>

#include "Component.h"
#include "GameObject.h"
#include "Matrix2D.h"
#include "Vector.h"

namespace GameEngine
{
constexpr float fullRotation = 360.0F;
constexpr float oneDegreeInRadians = fullRotation * 0.5F * std::numbers::inv_pi_v<float>;

const Vector2Df TransformComponent::defaultPosition = {0.0F, 0.0F};
const Vector2Df TransformComponent::defaultScale = {1.0F, 1.0F};

TransformComponent::TransformComponent(GameObject *gameObject) : Component(gameObject)
{
}

void TransformComponent::Update(float deltaTime)
{
}

const Vector2Df &TransformComponent::GetLocalPosition() const
{
    UpdateLocalTransform();
    return localPosition;
}

const Vector2Df &TransformComponent::GetLocalScale() const
{
    UpdateLocalTransform();
    return localScale;
}

const Vector2Df &TransformComponent::GetWorldPosition() const
{
    UpdateLocalTransform();
    if (parent == nullptr)
    {
        return GetLocalPosition();
    }

    SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
    return position;
}

const Vector2Df &TransformComponent::GetWorldScale() const
{
    UpdateLocalTransform();
    if (parent == nullptr)
    {
        return GetLocalScale();
    }

    SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
    return scale;
}

float TransformComponent::GetLocalRotation() const
{
    UpdateLocalTransform();
    return localRotation;
}

float TransformComponent::GetWorldRotation() const
{
    UpdateLocalTransform();
    if (parent == nullptr)
    {
        return GetLocalRotation();
    }

    SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
    return rotation;
}

Matrix2D TransformComponent::GetWorldTransform() const
{
    UpdateLocalTransform();

    if (parent == nullptr)
    {
        return localTransform;
    }

    return parent->GetWorldTransform() * localTransform;
}

TransformComponent *TransformComponent::GetParent() const
{
    return parent;
}

void TransformComponent::MoveBy(const Vector2Df &offset)
{
    localPosition += offset;
    isUpdated = false;
}

void TransformComponent::MoveBy(float offsetX, float offsetY)
{
    MoveBy({offsetX, offsetY});
}

void TransformComponent::Print() const
{
    std::cout << "Transform name : " << gameObject->GetName() << std::endl;

    std::cout << "Position" << std::endl;
    std::cout << "  World: (" << GetWorldPosition().x << ", " << GetWorldPosition().y << ")" << std::endl;
    std::cout << "  Local: (" << GetLocalPosition().x << ", " << GetLocalPosition().y << ")" << std::endl;

    std::cout << "Rotation" << std::endl;
    std::cout << "  World: " << GetWorldRotation() << std::endl;
    std::cout << "  Local: " << GetLocalRotation() << std::endl;

    std::cout << "Scale" << std::endl;
    std::cout << "  World: (" << GetWorldScale().x << ", " << GetWorldScale().y << ")" << std::endl;
    std::cout << "  Local: (" << GetLocalScale().x << ", " << GetLocalScale().y << ")" << std::endl;
}

void TransformComponent::RotateBy(const float offset)
{
    localRotation += offset;
    while (localRotation >= fullRotation)
    {
        localRotation -= fullRotation;
    }
    while (localRotation < 0.0F)
    {
        localRotation += fullRotation;
    }
    isUpdated = false;
}

void TransformComponent::ScaleBy(const Vector2Df &offset)
{
    localScale *= offset;
    isUpdated = false;
}

void TransformComponent::ScaleBy(float offsetX, float offsetY)
{
    ScaleBy({offsetX, offsetY});
}

void TransformComponent::SetLocalPosition(const Vector2Df &position)
{
    localPosition = position;
    isUpdated = false;
}

void TransformComponent::SetLocalPosition(float positionX, float positionY)
{
    SetLocalPosition({positionX, positionY});
}

void TransformComponent::SetLocalRotation(float angle)
{
    localRotation = angle;
    while (localRotation >= fullRotation)
    {
        localRotation -= fullRotation;
    }
    while (localRotation < 0.0F)
    {
        localRotation += fullRotation;
    }
    isUpdated = false;
}

void TransformComponent::SetLocalScale(const Vector2Df &scale)
{
    localScale = scale;
    isUpdated = false;
}

void TransformComponent::SetLocalScale(float scaleX, float scaleY)
{
    SetLocalScale({scaleX, scaleY});
}

void TransformComponent::SetParent(TransformComponent *newParent)
{
    if (parent == nullptr && newParent != nullptr)
    {
        newParent->gameObject->AddChild(gameObject);
        localTransform = newParent->GetWorldTransform().GetInversed() * localTransform;
    }
    else if (parent != nullptr && newParent == nullptr)
    {
        parent->gameObject->RemoveChild(gameObject);
        localTransform = parent->GetWorldTransform() * localTransform;
    }
    else if (parent != nullptr && newParent != nullptr)
    {
        parent->gameObject->RemoveChild(gameObject);
        newParent->gameObject->AddChild(gameObject);
        localTransform = newParent->GetWorldTransform().GetInversed() * (parent->GetWorldTransform() * localTransform);
    }

    SetLocalInfoFrom(localTransform);

    parent = newParent;
    isUpdated = false;
}

void TransformComponent::SetWorldPosition(const Vector2Df &position)
{
    if (parent == nullptr)
    {
        localPosition = position;
    }
    else
    {
        const Matrix2D newWorldTransform = CreateTransform(position, GetWorldRotation(), GetWorldScale());
        localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

        SetLocalInfoFrom(localTransform);
    }

    isUpdated = false;
}

void TransformComponent::SetWorldPosition(float positionX, float positionY)
{
    SetWorldPosition({positionX, positionY});
}

void TransformComponent::SetWorldRotation(float angle)
{
    if (parent == nullptr)
    {
        localRotation = angle;
    }
    else
    {
        const Matrix2D newWorldTransform = CreateTransform(GetWorldPosition(), angle, GetWorldScale());
        localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

        SetLocalInfoFrom(localTransform);
    }
    isUpdated = false;
}

void TransformComponent::SetWorldScale(const Vector2Df &newScale)
{
    if (parent == nullptr)
    {
        localScale = newScale;
    }
    else
    {
        const Matrix2D newWorldTransform = CreateTransform(GetWorldPosition(), GetWorldRotation(), newScale);
        localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

        SetLocalInfoFrom(localTransform);
    }

    isUpdated = false;
}

void TransformComponent::SetWorldScale(float scaleX, float scaleY)
{
    SetWorldScale({scaleX, scaleY});
}

Matrix2D TransformComponent::CreateTransform(const Vector2Df &position, const float rotation, const Vector2Df &scale)
{
    return Matrix2D(position, rotation, scale);
}

void TransformComponent::SetLocalInfoFrom(const Matrix2D &transform) const
{
    const auto &transformMatrix = transform.GetMatrix();

    localPosition.x = transformMatrix[0][2];
    localPosition.y = transformMatrix[1][2];

    localScale.x =
        std::sqrt((transformMatrix[0][0] * transformMatrix[0][0]) + (transformMatrix[1][0] * transformMatrix[1][0]));
    localScale.y =
        std::sqrt((transformMatrix[0][1] * transformMatrix[0][1]) + (transformMatrix[1][1] * transformMatrix[1][1]));

    localRotation = std::atan2(transformMatrix[0][1], transformMatrix[0][0]) * oneDegreeInRadians;
}

void TransformComponent::SetWorldInfoFrom(const Matrix2D &transform) const
{
    const auto &transformMatrix = transform.GetMatrix();

    position.x = transformMatrix[0][2];
    position.y = transformMatrix[1][2];

    scale.x =
        std::sqrt((transformMatrix[0][0] * transformMatrix[0][0]) + (transformMatrix[1][0] * transformMatrix[1][0]));
    scale.y =
        std::sqrt((transformMatrix[0][1] * transformMatrix[0][1]) + (transformMatrix[1][1] * transformMatrix[1][1]));

    rotation = std::atan2(transformMatrix[0][1], transformMatrix[0][0]) * oneDegreeInRadians;
}

void TransformComponent::UpdateLocalTransform() const
{
    if (!isUpdated)
    {
        localTransform = CreateTransform(localPosition, localRotation, localScale);
        isUpdated = true;
    }
}

void TransformComponent::UpdateLocalTransform(const Vector2Df &position, const float rotation,
                                              const Vector2Df &scale) const
{
    if (!isUpdated)
    {
        localTransform = CreateTransform(position, rotation, scale);
        isUpdated = true;
    }
}
} // namespace GameEngine