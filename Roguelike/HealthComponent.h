#pragma once
#include <memory>

#include "Component.h"
#include "IObserver.h"
#include "ISaveable.h"

namespace Roguelike
{
class HealthSave
{
    friend class HealthComponent;
    float maxHealth;
    float currentHealth;
};

class HealthComponent : public GameEngine::Component,
                        public GameEngine::IObservable,
                        public ISaveable<HealthComponent, HealthSave>
{
  public:
    explicit HealthComponent(GameEngine::GameObject *gameObject, const float maxHealth = 0.0F);

    void Update(float deltaTime) override;

    virtual float DecreaseHealth(const float damageAmount);
    virtual float IncreaseHealth(const float healingAmount);
    virtual void SetMaxHealth(const float newMaxHealth);

    bool IsAlive() const;
    float GetCurrentHealth() const;
    float GetMaxHealth() const;
    void LoadImpl(std::shared_ptr<const HealthSave> save);
    void SaveImpl(std::shared_ptr<HealthSave> save) const;
    void SetCurrentHealth(const float newCurrentHealth);

  protected:
    float maxHealth;
    float currentHealth;

  private:
    friend class ISaveable<HealthComponent, HealthSave>;
};
} // namespace Roguelike
