#pragma once
namespace Roguelike
{
class IDelayedAction
{
  public:
    void StartTimer(float delayDuration);

  protected:
    virtual void FinalAction() = 0;
    virtual void UpdateAction(float deltaTime) = 0;
    virtual void UpdateTimer(float deltaTime);

    float delayDuration = 0.0F;
    float currentTime = 0.0F;
};
} // namespace Roguelike
