#include "HealthComponent.h"

#include <cassert>
#include <memory>
#include <sstream>

#include "Component.h"
#include "GameObject.h"
#include "ISaveable.h"
#include "Logger.h"
#include "Utility.h"

namespace Roguelike
{
HealthComponent::HealthComponent(GameEngine::GameObject *gameObject, const float maxHealth)
    : Component(gameObject), maxHealth(maxHealth), currentHealth(maxHealth)
{
}

void HealthComponent::Update(float deltaTime)
{
}

float HealthComponent::DecreaseHealth(const float damageAmount)
{
    std::ostringstream message;
    message << this << " recieved " << damageAmount << " damage ";
    LOG_INFO(message.str());

    if (currentHealth <= 0.0F)
    {
        message.clear();
        message << "Trying to damage " << this << " which has 0.0F HP will have no effect";
        LOG_WARN(message.str());
        return damageAmount;
    }

    currentHealth -= damageAmount;
    if (currentHealth < 0.0F)
    {
        const float overDamage = -currentHealth;
        currentHealth = 0.0F;
        Emit();
        return overDamage;
    }
    Emit();
    return 0;
}

float HealthComponent::IncreaseHealth(const float healingAmount)
{
    std::ostringstream message;
    message << this << " recieved " << healingAmount << " healing ";
    LOG_INFO(message.str());

    message.clear();

    if (currentHealth >= maxHealth)
    {
        message << "Trying to heal " << this << " which has maximum HP will have no effect";
        LOG_WARN(message.str());
        message.clear();
        return healingAmount;
    }

    currentHealth += healingAmount;
    if (currentHealth > maxHealth)
    {
        const float overHeal = currentHealth - maxHealth;
        currentHealth = maxHealth;
        message << "Healing " << overHeal << " health points not applied due to going over maxHealth";
        LOG_INFO(message.str());
        message.clear();
        Emit();
        return overHeal;
    }
    Emit();
    return 0.0F;
}

void HealthComponent::SetMaxHealth(const float newMaxHealth)
{
    assert(newMaxHealth >= 0.0F && "maxHealth supposed to be positive");
    if (newMaxHealth < 0.0F)
    {
        LOG_WARN("maxHealth supposed to be positive")
    }
    maxHealth = newMaxHealth;
    Emit();
}

bool HealthComponent::IsAlive() const
{
    return currentHealth > 0.0F;
}

float Roguelike::HealthComponent::GetCurrentHealth() const
{
    return currentHealth;
}

float HealthComponent::GetMaxHealth() const
{
    return maxHealth;
}

void HealthComponent::LoadImpl(std::shared_ptr<const HealthSave> save)
{
    maxHealth = save->maxHealth;
    currentHealth = save->currentHealth;
    Emit();
}

void HealthComponent::SaveImpl(std::shared_ptr<HealthSave> save) const
{
    save->maxHealth = maxHealth;
    save->currentHealth = currentHealth;
}

void HealthComponent::SetCurrentHealth(const float newCurrentHealth)
{
    if (InRange(newCurrentHealth, 0.0F, maxHealth))
    {
        currentHealth = newCurrentHealth;
        Emit();
    }
}
} // namespace Roguelike