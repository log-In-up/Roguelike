#pragma once
#include "Component.h"
#include "GameObject.h"

namespace GameEngine
{
	class AttackComponent : public Component
	{
	public:
		AttackComponent(GameObject* gameObject, float attackPower);

		float GetAttackPower() const
		{
			return attackPower;
		}

		void SetAttackPower(float value)
		{
			attackPower = value;
		}

		void Attack(GameObject* target) const;
		void Render(sf::RenderWindow& window) override;
		void Update(float deltaTime) override;
	private:
		float attackPower;
	};
}