#pragma once
#include <iostream>
#include <map>

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Vector.h"

namespace GameEngine
{
	class PhysicsSystem
	{
	private:
		std::vector<ColliderComponent*> colliders;
		std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;

		float fixedDeltaTime = 0.02f;
	public:
		static PhysicsSystem* Instance();

		float GetFixedDeltaTime() const;
		void Subscribe(ColliderComponent* collider);
		void Unsubscribe(ColliderComponent* collider);
		void Update();
	private:
		PhysicsSystem() {}
		~PhysicsSystem() {}

		PhysicsSystem(PhysicsSystem const&) = delete;
		PhysicsSystem& operator= (PhysicsSystem const&) = delete;
	};
}