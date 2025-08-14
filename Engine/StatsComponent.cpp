#include "pch.h"
#include "StatsComponent.h"

namespace GameEngine
{
	StatsComponent::StatsComponent(GameObject* gameObject, float health, float armor)
		: Component(gameObject), currentHealth(health), maxHealth(health), armor(armor)
	{
	}

	void StatsComponent::Heal(float value)
	{
		currentHealth += value;

		if (currentHealth > maxHealth)
		{
			currentHealth = maxHealth;
		}
	}

	void StatsComponent::Render(sf::RenderWindow& window)
	{
	}

	void StatsComponent::TakeDamage(float value)
	{
		value -= armor;
		if (value < 0.f)
		{
			value = 0.f;
		}

		armor -= 1.f;
		if (armor < 0.f)
		{
			armor = 0.f;
		}

		currentHealth -= value;

		if (currentHealth <= 0.f)
		{
			currentHealth = 0.f;
		}
	}

	void StatsComponent::Update(float deltaTime)
	{
	}
}