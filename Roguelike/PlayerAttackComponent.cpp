#include "PlayerAttackComponent.h"

#include <map>
#include <memory>
#include <utility>

#include "ActorRegisterSystem.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "IObserver.h"
#include "InputComponent.h"
#include "Logger.h"
#include "Settings.h"

namespace Roguelike
{
PlayerAttackComponent::PlayerAttackComponent(GameEngine::GameObject *gameObject, const Parameters &atackParameters,
                                             std::weak_ptr<GameEngine::GameObject> target)
    : AttackComponent(gameObject, atackParameters, target)
{
}

void PlayerAttackComponent::Notify(std::shared_ptr<GameEngine::IObservable> observable)
{
    if (auto input = std::dynamic_pointer_cast<GameEngine::InputComponent>(observable))
    {
        if (input->GetAttack())
        {
            if (currentCooldown <= 0.0F)
            {
                currentCooldown = cooldown;
                const auto position = gameObject->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition();

                auto targetsVector =
                    ActorRegisterSystem::Instance()->GetActorsNotInGroupList(ActorsGroups::PlayerGroup);

                std::map<float, GameEngine::GameObject *> targets;

                for (auto &possibleTarget : targetsVector)
                {
                    if (possibleTarget->GetComponent<HealthComponent>()->IsAlive())
                    {
                        const auto targetPosition =
                            possibleTarget->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition();

                        const auto distance = (targetPosition - position).GetLength();
                        targets.emplace(std::pair<float, GameEngine::GameObject *>(distance, possibleTarget));
                    }
                }
                auto newTarget = targets.begin();
                if (newTarget != targets.end())
                {
                    target = newTarget->second->weak_from_this();
                }
                else
                {
                    target = std::weak_ptr<GameEngine::GameObject>();
                }
                StartAttack();
            }
            else
            {
                LOG_INFO("Attack is on cooldown");
            }
        }
    }
}
} // namespace Roguelike