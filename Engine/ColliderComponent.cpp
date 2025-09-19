#include "pch.h"

#include <algorithm>
#include <functional>

#include "ColliderComponent.h"
#include "Collision.h"
#include "Component.h"
#include "GameObject.h"
#include "Trigger.h"

namespace GameEngine
{
ColliderComponent::ColliderComponent(GameObject *gameObject) : Component(gameObject)
{
}

void ColliderComponent::SetTrigger(bool newIsTrigger)
{
    isTrigger = newIsTrigger;
}

void ColliderComponent::SubscribeCollision(std::function<void(Collision)> onCollisionAction)
{
    onCollisionActions.push_back(onCollisionAction);
}

void ColliderComponent::SubscribeTriggerEntered(std::function<void(Trigger)> onTriggerEntered)
{
    onTriggerEnteredActions.push_back(onTriggerEntered);
}

void ColliderComponent::SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExit)
{
    onTriggerExitActions.push_back(onTriggerExit);
}

void ColliderComponent::UnsubscribeCollision(std::function<void(Collision)> onCollisionAction)
{
    onCollisionActions.erase(std::remove_if(onCollisionActions.begin(), onCollisionActions.end(),
                                            [&onCollisionAction](const std::function<void(Collision)> &action) {
                                                return onCollisionAction.target<void(Collision)>() ==
                                                       action.target<void(Collision)>();
                                            }),
                             onCollisionActions.end());
}

void ColliderComponent::UnsubscribeTriggerEntered(std::function<void(Trigger)> onTriggerEntered)
{
    onTriggerEnteredActions.erase(std::remove_if(onTriggerEnteredActions.begin(), onTriggerEnteredActions.end(),
                                                 [&onTriggerEntered](const std::function<void(Trigger)> &action) {
                                                     return onTriggerEntered.target<void(Trigger)>() ==
                                                            action.target<void(Trigger)>();
                                                 }),
                                  onTriggerEnteredActions.end());
}

void ColliderComponent::UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExit)
{
    onTriggerExitActions.erase(std::remove_if(onTriggerExitActions.begin(), onTriggerExitActions.end(),
                                              [&onTriggerExit](const std::function<void(Trigger)> &action) {
                                                  return onTriggerExit.target<void(Trigger)>() ==
                                                         action.target<void(Trigger)>();
                                              }),
                               onTriggerExitActions.end());
}

void ColliderComponent::OnCollision(Collision collision)
{
    for (auto &action : onCollisionActions)
    {
        action(collision);
    }
}

void ColliderComponent::OnTriggerEntered(Trigger trigger)
{
    for (auto &action : onTriggerEnteredActions)
    {
        action(trigger);
    }
}

void ColliderComponent::OnTriggerExit(Trigger trigger)
{
    for (auto &action : onTriggerExitActions)
    {
        action(trigger);
    }
}
} // namespace GameEngine