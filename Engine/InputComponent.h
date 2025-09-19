#pragma once
#include "Component.h"
#include "IObserver.h"

namespace GameEngine
{
class InputComponent : public Component, public IObservable
{
  public:
    explicit InputComponent(GameObject *gameObject);

    void Update(float deltaTime) override = 0;

    bool GetAttack() const;
    bool GetBlock() const;
    bool GetLevelTransfer() const;
    float GetHorizontalAxis() const;
    float GetVerticalAxis() const;

  protected:
    float horizontalAxis = 0.0F;
    float verticalAxis = 0.0F;
    bool attack = false;
    bool block = false;
    bool levelTransfer = false;
};
} // namespace GameEngine
