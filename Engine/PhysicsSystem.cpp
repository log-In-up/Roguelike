#include "pch.h"

#include "PhysicsSystem.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include <SFML/Graphics/Rect.hpp>

#include "ColliderComponent.h"
#include "Collision.h"
#include "GameObject.h"
#include "Logger.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "Trigger.h"
#include "Vector.h"

namespace GameEngine
{
PhysicsSystem *PhysicsSystem::Instance()
{
    static PhysicsSystem physicSystem;
    return &physicSystem;
}

void PhysicsSystem::Update()
{
    for (int i = 0; i < colliders.size(); ++i)
    {
        auto *body = colliders[i]->GetGameObject()->GetComponent<RigidBodyComponent>();

        if (body != nullptr && body->GetKinematic())
        {
            continue;
        }

        for (int j = 0; j < colliders.size(); ++j)
        {
            if (i == j)
            {
                continue;
            }
            sf::FloatRect intersection;
            if (colliders[i]->bounds.intersects(colliders[j]->bounds, intersection))
            {
                if (colliders[i]->isTrigger != colliders[j]->isTrigger)
                {
                    auto *trigger = new Trigger(colliders[i], colliders[j]);
                    ProcessTriggerEnter(trigger);
                    delete trigger;
                }
                else if (!colliders[i]->isTrigger)
                {
                    auto *collision = new Collision(colliders[i], colliders[j], intersection);
                    ProcessCollision(collision);
                    delete collision;
                }
            }
        }
    }

    for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair;
         triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
    {
        ++nextTriggeredPair;
        if (!triggeredPair->first->bounds.intersects(triggeredPair->second->bounds))
        {
            std::ostringstream message;
            message << "Exited trigger " << triggeredPair->first << " " << triggeredPair->second;
            auto *trigger = new Trigger(triggeredPair->first, triggeredPair->second);
            triggeredPair->first->OnTriggerExit(*trigger);
            triggeredPair->second->OnTriggerExit(*trigger);
            delete trigger;

            triggersEnteredPair.erase(triggeredPair);
        }
    }
}

void PhysicsSystem::Subscribe(ColliderComponent *collider)
{
    std::ostringstream message;
    message << "Subscribe collider " << collider;
    LOG_INFO(message.str());

    colliders.push_back(collider);
}

void PhysicsSystem::Unsubscribe(ColliderComponent *collider)
{
    std::ostringstream message;
    message << "Unsubscribe collider " << collider;
    LOG_INFO(message.str());

    // Process trigger exit if collider was in triggeredPair
    for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair;
         triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
    {
        ++nextTriggeredPair;
        if (triggeredPair->first == collider || triggeredPair->second == collider)
        {
            std::ostringstream message;
            message << "Exited trigger " << triggeredPair->first << " " << triggeredPair->second;
            auto *trigger = new Trigger(triggeredPair->first, triggeredPair->second);
            triggeredPair->first == collider ? triggeredPair->second->OnTriggerExit(*trigger)
                                             : triggeredPair->first->OnTriggerExit(*trigger);
            delete trigger;
            triggersEnteredPair.erase(triggeredPair);
        }
    }

    colliders.erase(std::remove_if(colliders.begin(), colliders.end(),
                                   [collider](ColliderComponent *obj) { return collider == obj; }),
                    colliders.end());
}

void PhysicsSystem::ProcessCollision(Collision *collision)
{
    constexpr float half = 0.5F;
    const auto &intersection = collision->collisionRect;
    const Vector2Df intersectionPosition = {intersection.left - (half * intersection.width),
                                            intersection.top - (half * intersection.height)};

    const Vector2Df aPosition = {collision->first->bounds.left, collision->first->bounds.top};

    auto *aTransform = collision->first->GetGameObject()->GetComponent<TransformComponent>();

    std::ostringstream message;
    if (intersection.width > intersection.height)
    {
        if (intersectionPosition.y > aPosition.y)
        {
            aTransform->MoveBy(0.0F, -intersection.height);
            message << "Top collision " << collision->first << " " << collision->second;
            LOG_INFO(message.str());
        }
        else
        {
            aTransform->MoveBy(0.0F, intersection.height);
            message << "Bottom collision " << collision->first << " " << collision->second;
            LOG_INFO(message.str());
        }
    }
    else
    {
        if (intersectionPosition.x > aPosition.x)
        {
            aTransform->MoveBy(-intersection.width, 0.0F);
            message << "Rigth collision " << collision->first << " " << collision->second;
            LOG_INFO(message.str());
        }
        else
        {
            aTransform->MoveBy(intersection.width, 0.0F);
            message << "Left collision " << collision->first << " " << collision->second;
            LOG_INFO(message.str());
        }
    }

    collision->first->OnCollision(*collision);
    collision->second->OnCollision(*collision);
}

void PhysicsSystem::ProcessTriggerEnter(Trigger *trigger)
{
    auto *const triggerCollider = trigger->first->isTrigger ? trigger->first : trigger->second;
    auto *const objectCollider = trigger->first->isTrigger ? trigger->second : trigger->first;
    auto triggeredPairs = triggersEnteredPair.equal_range(triggerCollider);
    bool isAlreadyTriggered = false;
    for (auto triggerPair = triggeredPairs.first; triggerPair != triggeredPairs.second; triggerPair++)
    {
        if (triggerPair->second == objectCollider)
        {
            isAlreadyTriggered = true;
            break;
        }
    }
    if (!isAlreadyTriggered)
    {
        std::ostringstream message;
        message << "Entered trigger " << trigger->first << " " << trigger->second;
        LOG_INFO(message.str());

        trigger->first->OnTriggerEntered(*trigger);
        trigger->second->OnTriggerEntered(*trigger);

        triggersEnteredPair.emplace(triggerCollider, objectCollider);
    }
}
} // namespace GameEngine