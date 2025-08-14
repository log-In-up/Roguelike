#pragma once
#include "Component.h"

namespace GameEngine
{
	class StatsComponent : public Component
	{
	public:
		StatsComponent(GameObject* gameObject, float health, float armor);

		float GetArmor() const
		{
			return armor;
		}

		float GetCurrentHealth() const
		{
			return currentHealth;
		}

		float GetMaxHealth() const
		{
			return maxHealth;
		}

		void Heal(float value);
		void Render(sf::RenderWindow& window) override;
		void TakeDamage(float value);
		void Update(float deltaTime) override;
	private:
		float armor;
		float currentHealth;
		float maxHealth;
	};
}