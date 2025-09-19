#include "AITargetSelector.h"

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "AIAttackComponent.h"
#include "AIBlackboard.h"
#include "ActorComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "IObserver.h"
#include "PerceptionComponent.h"
#include "Settings.h"

namespace Roguelike
{
AITargetSelector::AITargetSelector(GameEngine::GameObject *gameObject) : Component(gameObject)
{
}

void AITargetSelector::Notify(std::shared_ptr<GameEngine::IObservable> observable)
{
    if (std::dynamic_pointer_cast<PerceptionComponent>(observable))
    {
        UpdateTarget();
    }
}

void AITargetSelector::Update(float deltaTime)
{
}

void AITargetSelector::UpdateTarget()
{
    auto *blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (blackBoard != nullptr)
    {
        std::vector<GameEngine::GameObject *> *detectedActors = nullptr;
        blackBoard->Get("Detected Actors", detectedActors);

        std::map<float, GameEngine::GameObject *> targets;
        if (detectedActors != nullptr)
        {
            const auto &position = gameObject->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition();

            for (auto &actor : *detectedActors)
            {
                if (actor->GetComponent<ActorComponent>()->GetGroupID() == ActorsGroups::PlayerGroup)
                {
                    auto between = actor->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition() - position;
                    targets.emplace(std::pair<float, GameEngine::GameObject *>(between.GetLength(), actor));
                }
            }
        }
        if (!targets.empty())
        {
            blackBoard->Set("isTargetVisible", true);
            blackBoard->Set(
                "lastTargetPosition",
                targets.begin()->second->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition());
            blackBoard->Set("lastTarget", targets.begin()->second);

            if (auto *attackComponent = gameObject->GetComponent<AIAttackComponent>())
            {
                attackComponent->SetTarget(targets.begin()->second->weak_from_this());
            }

            Emit();
        }
        else
        {
            blackBoard->Set("isTargetVisible", false);
        }
    }
}
} // namespace Roguelike