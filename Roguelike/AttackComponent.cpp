#include "AttackComponent.h"

#include <cassert>
#include <memory>

#include "ArmorComponent.h"
#include "BlockComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Logger.h"
#include "SpriteAnimationComponent.h"

namespace Roguelike
{
const AttackComponent::Parameters AttackComponent::defaultParameters = {
    .startupTime = 0.0F, .cooldown = 0.0F, .damage = 0.0F, .range = 0.0F};

AttackComponent::AttackComponent(GameEngine::GameObject *gameObject, const Parameters &atackParameters,
                                 std::weak_ptr<GameEngine::GameObject> target)
    : Component(gameObject), target(target), startupTime(atackParameters.startupTime), timeTillAttack(0.0F),
      currentCooldown(0.0F), cooldown(atackParameters.cooldown), damage(atackParameters.damage),
      range(atackParameters.range)
{
    healtComponentPtr = gameObject->GetComponentSharedPtr<HealthComponent>();
}

void AttackComponent::Update(float deltaTime)
{
    if (currentCooldown > 0.0F)
    {
        currentCooldown -= deltaTime;
    }
    if (timeTillAttack > 0.0F)
    {
        bool interupted = false;
        if (auto *blockComponent = gameObject->GetComponent<BlockComponent>())
        {
            if (blockComponent->GetIsBlocking())
            {
                LOG_INFO("Attack interupted by blocking");
                if (auto *spriteAnimation = gameObject->GetComponent<GameEngine::SpriteAnimationComponent>())
                {
                    spriteAnimation->StartAnimation("Idle", true);
                }
                timeTillAttack = 0.0F;
                interupted = true;
            }
        }
        if (!interupted)
        {
            timeTillAttack -= deltaTime;
            if (timeTillAttack <= 0.0F)
            {
                ProcessAttack();
            }
        }
    }
}

void AttackComponent::ProcessAttack()
{
    auto healthComponent = healtComponentPtr.lock();
    if (healthComponent && healthComponent->IsAlive())
    {
        if (auto *spriteAnimation = gameObject->GetComponent<GameEngine::SpriteAnimationComponent>())
        {
            spriteAnimation->StartAnimation("Attack");
        }
        auto *attacker = gameObject;
        if (auto targetPtr = target.lock())
        {
            auto distance = (targetPtr->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition() -
                             attacker->GetComponent<GameEngine::TransformComponent>()->GetWorldPosition())
                                .GetLength();
            if (distance > range)
            {
                LOG_INFO("Target is out of attack range");
                return;
            }
            auto damageLeft = damage;
            if (auto *block = targetPtr->GetComponent<BlockComponent>())
            {
                damageLeft = block->ApplyDamage(damageLeft);
                if (damageLeft <= 0.0F)
                {
                    return;
                }
            }
            if (auto *armor = targetPtr->GetComponent<ArmorComponent>())
            {
                damageLeft = armor->ApplyDamage(damageLeft);
                if (!armor->IsNotBroken())
                {
                    targetPtr->RemoveComponent(armor);
                }
                if (damageLeft <= 0.0F)
                {
                    return;
                }
            }
            if (auto *health = targetPtr->GetComponent<HealthComponent>())
            {
                health->DecreaseHealth(damageLeft);
            }
        }
        else
        {
            LOG_WARN("Target not selected or expired");
        }
    }
}

void AttackComponent::StartAttack()
{
    auto healthComponent = healtComponentPtr.lock();
    if (healthComponent && healthComponent->IsAlive())
    {
        if (auto *blockComponent = gameObject->GetComponent<BlockComponent>())
        {
            if (blockComponent->GetIsBlocking())
            {
                LOG_INFO("Can't start attack while bloking");
                return;
            }
        }
        if (auto *spriteAnimation = gameObject->GetComponent<GameEngine::SpriteAnimationComponent>())
        {
            spriteAnimation->StartAnimation("Attack windup");
        }
        currentCooldown = cooldown;
        timeTillAttack = startupTime;
    }
}

float AttackComponent::GetCooldown() const
{
    return cooldown;
}

float AttackComponent::GetCurrentCooldown() const
{
    return currentCooldown;
}

float AttackComponent::GetDamage() const
{
    return damage;
}

float AttackComponent::GetRange() const
{
    return range;
}

float AttackComponent::GetStartupTime() const
{
    return startupTime;
}

float AttackComponent::GetTimeTillAttack() const
{
    return timeTillAttack;
}

std::shared_ptr<GameEngine::GameObject> AttackComponent::GetTarget() const
{
    if (!target.expired())
    {
        return target.lock();
    }
    return std::shared_ptr<GameEngine::GameObject>();
}

void AttackComponent::SetCooldown(const float newCoolDown)
{
    assert(newCoolDown >= 0.0F && "cooldown should be positive");
    if (newCoolDown >= 0.0F)
    {
        cooldown = newCoolDown;
    }
    else
    {
        LOG_WARN("Trying to set negative cooldown - no changes applied");
    }
}

void AttackComponent::SetDamage(const float newDamage)
{
    assert(newDamage >= 0.0F && "damage should be positive");
    if (newDamage >= 0.0F)
    {
        damage = newDamage;
    }
    else
    {
        LOG_WARN("Trying to set negative damage - no changes applied");
    }
}

void AttackComponent::SetRange(const float newRange)
{
    assert(newRange >= 0.0F && "Range should be positive");
    if (newRange >= 0.0F)
    {
        range = newRange;
    }
    else
    {
        LOG_WARN("Trying to set negative range - no changes applied");
    }
}

void AttackComponent::SetStartupTime(const float newStartupTime)
{
    assert(newStartupTime >= 0.0F && "startupTime should be positive");
    if (newStartupTime >= 0.0F)
    {
        startupTime = newStartupTime;
    }
    else
    {
        LOG_WARN("Trying to set negative startupTime - no changes applied");
    }
}

void AttackComponent::SetTarget(std::weak_ptr<GameEngine::GameObject> newTarget)
{
    target = newTarget;
}
} // namespace Roguelike