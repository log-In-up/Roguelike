#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Collision.h"
#include "Component.h"
#include "PhysicsSystem.h"
#include "Trigger.h"

namespace GameEngine
{
	class ColliderComponent : public Component
	{
	protected:
		sf::FloatRect bounds;

		std::vector<std::function<void(Collision)>> onCollisionActions;
		std::vector<std::function<void(Trigger)>> onTriggerEnterActions;
		std::vector<std::function<void(Trigger)>> onTriggerExitActions;

		bool isTrigger = false;
	public:
		ColliderComponent(GameObject* gameObject);

		virtual void Render(sf::RenderWindow& window) = 0;
		virtual void Update(float deltaTime) = 0;

		void SetTrigger(bool newIsTrigger);
		void SubscribeCollision(std::function<void(Collision)> onCollisionAction);
		void SubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);
		void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);
		void UnsubscribeCollision(std::function<void(Collision)> onCollisionAction);
		void UnsubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);
		void UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);

		friend class PhysicsSystem;

	protected:
		void OnCollision(Collision collision);
		void OnTriggerEnter(Trigger trigger);
		void OnTriggerExit(Trigger trigger);
	};
}