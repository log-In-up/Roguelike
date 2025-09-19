#include "IDelayedAction.h"

namespace Roguelike
{
void IDelayedAction::StartTimer(float delayDuration)
{
    IDelayedAction::delayDuration = delayDuration;
    currentTime = delayDuration;
}

void IDelayedAction::UpdateTimer(float deltaTime)
{
    if (currentTime > 0.0F)
    {
        currentTime -= deltaTime;
        UpdateAction(deltaTime);

        if (currentTime <= 0.0F)
        {
            FinalAction();
        }
    }
}
} // namespace Roguelike