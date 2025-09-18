#include "ArmorComponent.h"

#include <algorithm>
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
const ArmorComponent::Parameters ArmorComponent::defaultParameters = {.maxArmorPoints = 0.0F, .damageReduction = 1.0F};

ArmorComponent::ArmorComponent(GameEngine::GameObject *gameObject, const ArmorComponent::Parameters &parameters)
    : Component(gameObject), maxArmorPoints(parameters.maxArmorPoints), currentArmorPoints(parameters.maxArmorPoints),
      damageReduction(parameters.damageReduction)
{
}

void ArmorComponent::Update(float deltaTime)
{
}

bool ArmorComponent::IsNotBroken() const
{
    return currentArmorPoints > 0.0F;
}

float ArmorComponent::GetCurrentArmorPoints() const
{
    return currentArmorPoints;
}

float ArmorComponent::GetDamageReduction() const
{
    return damageReduction;
}

float ArmorComponent::GetMaxArmorPoints() const
{
    return maxArmorPoints;
}

float ArmorComponent::ApplyDamage(const float damageAmount)
{
    std::ostringstream message;

    if (currentArmorPoints <= 0.0F)
    {
        message << "Trying to damage " << this << " which has 0.0F armorPoints will have no effect";
        LOG_WARN(message.str());
        message.clear();
    }

    const float absorbedDamage = std::min(currentArmorPoints, (damageAmount * damageReduction));
    message << this << " recieved " << damageAmount << " damage - " << absorbedDamage << " absorbed";
    LOG_INFO(message.str());
    currentArmorPoints -= absorbedDamage;
    Emit();
    return damageAmount - absorbedDamage > 0.0F ? damageAmount - absorbedDamage : 0.0F;
}

float ArmorComponent::IncreaseArmorPoints(const float armorPointAmount)
{
    std::ostringstream message;
    message << this << " recieved " << armorPointAmount << " armorPoints ";
    LOG_INFO(message.str());
    message.clear();

    if (currentArmorPoints >= maxArmorPoints)
    {
        message << "Trying to restore armor " << this << " which has maximum ArmorPoints will have no effect";
        LOG_WARN(message.str());
        message.clear();
    }

    currentArmorPoints += armorPointAmount;
    if (currentArmorPoints > currentArmorPoints)
    {
        const float overArmorRestore = currentArmorPoints - maxArmorPoints;
        currentArmorPoints = maxArmorPoints;

        message << "Restoring " << overArmorRestore << " not applied due to going over maxArmorPoints";
        LOG_INFO(message.str());
        message.clear();

        Emit();
        return overArmorRestore;
    }
    Emit();
    return 0.0F;
}

void ArmorComponent::SetCurrentArmorPoints(const float newCurrentArmorPoints)
{
    assert(newCurrentArmorPoints >= 0 && "currentArmorPoints supposed to be positive");
    if (newCurrentArmorPoints < 0.0F)
    {
        LOG_WARN("currentArmorPoints supposed to be positive - setted to 0");
        currentArmorPoints = 0.0F;
        Emit();
        return;
    }
    currentArmorPoints = newCurrentArmorPoints;
    Emit();
}

void ArmorComponent::SetDamageReduction(const float newDamageReduction)
{
    assert((newDamageReduction >= 0.0F && newDamageReduction <= 1.0F) &&
           "newDamageReduction supposed to be in range 0.0F - 1.f");
    if (!InRange(newDamageReduction, 0.0F, 1.0F))
    {
        LOG_WARN("newDamageReduction supposed to be in range 0.0F - 1.0F. Setted to "
                 "1.0F");
        damageReduction = 1.0F;
        return;
    }
    damageReduction = newDamageReduction;
}

void ArmorComponent::SetMaxArmorPoints(const float newMaxArmorPoints)
{
    assert(newMaxArmorPoints >= 0 && "maxArmorPoints supposed to be positive");
    if (newMaxArmorPoints < 0.0F)
    {
        LOG_WARN("maxArmorPoints supposed to be positive - setted to 0");
        maxArmorPoints = 0.0F;
        return;
    }
    maxArmorPoints = newMaxArmorPoints;
    Emit();
}

void ArmorComponent::LoadImpl(std::shared_ptr<const ArmorSave> save)
{
    maxArmorPoints = save->maxArmorPoints;
    currentArmorPoints = save->currentArmorPoints;
    damageReduction = save->damageReduction;
    Emit();
}

void ArmorComponent::SaveImpl(std::shared_ptr<ArmorSave> save) const
{
    save->maxArmorPoints = maxArmorPoints;
    save->currentArmorPoints = currentArmorPoints;
    save->damageReduction = damageReduction;
}
} // namespace Roguelike