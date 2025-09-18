#pragma once
#include "Component.h"
#include "Matrix2D.h"
#include "Vector.h"

namespace GameEngine
{
class GameObject;

class TransformComponent : public Component
{
  public:
    explicit TransformComponent(GameObject *gameObject);

    void Update(float deltaTime) override;

    const Vector2Df &GetLocalPosition() const;
    const Vector2Df &GetLocalScale() const;
    const Vector2Df &GetWorldPosition() const;
    const Vector2Df &GetWorldScale() const;
    float GetLocalRotation() const;
    float GetWorldRotation() const;
    Matrix2D GetWorldTransform() const;
    TransformComponent *GetParent() const;
    void MoveBy(const Vector2Df &offset);
    void MoveBy(float offsetX, float offsetY);
    void Print() const;
    void RotateBy(const float offset);
    void ScaleBy(const Vector2Df &offset);
    void ScaleBy(float offsetX, float offsetY);
    void SetLocalPosition(const Vector2Df &position);
    void SetLocalPosition(float positionX, float positionY);
    void SetLocalRotation(float angle);
    void SetLocalScale(const Vector2Df &scale);
    void SetLocalScale(float scaleX, float scaleY);
    void SetParent(TransformComponent *newParent);
    void SetWorldPosition(const Vector2Df &position);
    void SetWorldPosition(float positionX, float positionY);
    void SetWorldRotation(float angle);
    void SetWorldScale(const Vector2Df &scale);
    void SetWorldScale(float scaleX, float scaleY);

  private:
    static Matrix2D CreateTransform(const Vector2Df &position, const float rotation, const Vector2Df &scale);
    void SetLocalInfoFrom(const Matrix2D &transform) const;
    void SetWorldInfoFrom(const Matrix2D &transform) const;
    void UpdateLocalTransform() const;
    void UpdateLocalTransform(const Vector2Df &position, const float rotation, const Vector2Df &scale) const;

    static const Vector2Df defaultScale;
    static const Vector2Df defaultPosition;
    TransformComponent *parent = nullptr;

    mutable Matrix2D localTransform;

    mutable Vector2Df localPosition = defaultPosition;
    mutable float localRotation = 0.0F;
    mutable Vector2Df localScale = defaultScale;

    mutable Vector2Df position = defaultPosition;
    mutable float rotation = 0.0F;
    mutable Vector2Df scale = defaultScale;

    mutable bool isUpdated = false;
};
} // namespace GameEngine
