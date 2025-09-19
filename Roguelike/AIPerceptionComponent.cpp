#include "AIPerceptionComponent.h"

#include <memory>

#include "AIBlackboard.h"
#include "AIInputComponent.h"
#include "GameObject.h"
#include "IObserver.h"
#include "Logger.h"
#include "PerceptionComponent.h"

namespace Roguelike
{
AIPerceptionComponent::AIPerceptionComponent(GameEngine::GameObject *gameObject,
                                             const PerceptionComponent::Parameters &parameters)
    : PerceptionComponent(gameObject, parameters)
{
    auto *blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (blackBoard != nullptr)
    {
        blackBoard->Set("Detected Actors", &detectedActors);
    }
    else
    {
        LOG_ERROR("AIBlackboard required for AIPerceptionComponent");
        gameObject->RemoveComponent(this);
        return;
    }
}

void AIPerceptionComponent::Notify(std::shared_ptr<IObservable> observable)
{
    if (auto input = std::dynamic_pointer_cast<AIInputComponent>(observable))
    {
        SetVisionDirection(input->GetDirection());
    }
}
} // namespace Roguelike