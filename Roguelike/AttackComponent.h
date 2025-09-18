#pragma once
#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "HealthComponent.h"

namespace Roguelike
{
class AttackComponent : public GameEngine::Component
{
  public:
    struct Parameters
    {
        float startupTime;
        float cooldown;
        float damage;
        float range;
    };
    explicit AttackComponent(GameEngine::GameObject *gameObject, const Parameters &atackParameters = defaultParameters,
                             std::weak_ptr<GameEngine::GameObject> target = std::weak_ptr<GameEngine::GameObject>());

    void Update(float deltaTime) override;

    virtual void ProcessAttack();
    virtual void StartAttack();

    float GetCooldown() const;
    float GetCurrentCooldown() const;
    float GetDamage() const;
    float GetRange() const;
    float GetStartupTime() const;
    float GetTimeTillAttack() const;
    std::shared_ptr<GameEngine::GameObject> GetTarget() const;
    void SetCooldown(const float newCoolDown);
    void SetDamage(const float newDamage);
    void SetRange(const float newRange);
    void SetStartupTime(const float newStartupTime);
    void SetTarget(std::weak_ptr<GameEngine::GameObject> newTarget);

  protected:
    static const Parameters defaultParameters;
    std::weak_ptr<GameEngine::GameObject> target;
    std::weak_ptr<HealthComponent> healtComponentPtr;
    float startupTime;
    float timeTillAttack;
    float currentCooldown;
    float cooldown;
    float damage;
    float range;
};
} // namespace Roguelike
