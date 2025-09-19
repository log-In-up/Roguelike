#include "LabyrinthExit.h"

#include <memory>

#include "Floor.h"
#include "GameObject.h"
#include "LevelCompleteCondition.h"
#include "LevelManager.h"
#include "RigidBodyComponent.h"
#include "SpriteColliderComponent.h"
#include "Trigger.h"
#include "Vector.h"

namespace Roguelike
{
LabyrinthExit::LabyrinthExit(GameEngine::Vector2Df position, int textureIndex, GameEngine::Vector2Di size)
    : Floor(position, textureIndex, size)
{
    auto exitTrigger = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
    exitTrigger->SetTrigger(true);

    auto onEnter = [](GameEngine::Trigger trigger) {
        auto conditions = LevelManager::Instance()->GetCompleteConditions();
        for (auto condition : conditions)
        {
            if (auto exitCondition = std::dynamic_pointer_cast<ExitReached>(condition))
            {
                exitCondition->CheckExited(trigger, true);
            }
        }
    };
    exitTrigger->SubscribeTriggerEntered(onEnter);

    auto onExit = [](GameEngine::Trigger trigger) {
        auto conditions = LevelManager::Instance()->GetCompleteConditions();
        for (auto condition : conditions)
        {
            if (auto exitCondition = std::dynamic_pointer_cast<ExitReached>(condition))
            {
                exitCondition->CheckExited(trigger, false);
            }
        }
    };
    exitTrigger->SubscribeTriggerExit(onExit);

    auto rigidBody = gameObject->AddComponent<GameEngine::RigidBodyComponent>();
    rigidBody->SetKinematic(false);
}
} // namespace Roguelike