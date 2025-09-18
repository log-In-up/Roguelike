#pragma once
#include <functional>
#include <vector>

#include <SFML/Graphics/Rect.hpp>

#include "Collision.h"
#include "Component.h"
#include "Trigger.h"

namespace GameEngine
{
class ColliderComponent : public Component
{
  public:
    friend class PhysicsSystem;

    explicit ColliderComponent(GameObject *gameObject);

    void Update(float deltaTime) override = 0;

    void SetTrigger(bool newIsTrigger);
    void SubscribeCollision(std::function<void(Collision)> onCollisionAction);
    void SubscribeTriggerEntered(std::function<void(Trigger)> onTriggerEntered);
    void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExit);
    void UnsubscribeCollision(std::function<void(Collision)> onCollisionAction);
    void UnsubscribeTriggerEntered(std::function<void(Trigger)> onTriggerEntered);
    void UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExit);

  protected:
    void OnCollision(Collision collision);
    void OnTriggerEntered(Trigger trigger);
    void OnTriggerExit(Trigger trigger);

    std::vector<std::function<void(Collision)>> onCollisionActions;
    std::vector<std::function<void(Trigger)>> onTriggerEnteredActions;
    std::vector<std::function<void(Trigger)>> onTriggerExitActions;

    sf::FloatRect bounds;
    bool isTrigger = false;
};
} // namespace GameEngine
