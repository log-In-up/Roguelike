#include "pch.h"
#include "AttackComponent.h"
#include "StatsComponent.h"

namespace GameEngine
{
	AttackComponent::AttackComponent(GameObject* gameObject, float attackPower)
		: Component(gameObject), attackPower(attackPower)
	{
	}

	void AttackComponent::Attack(GameObject* target) const
	{
		if (!target)
		{
			return;
		}

		auto targetStatsComponent = target->GetComponent<StatsComponent>();

		if (targetStatsComponent)
		{
			float damage = attackPower;
			targetStatsComponent->TakeDamage(damage);
		}
	}

	void AttackComponent::Render(sf::RenderWindow& window)
	{
	}

	void AttackComponent::Update(float deltaTime)
	{
	}
}