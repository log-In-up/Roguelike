#pragma once
#include <memory>

#include "Component.h"
#include "IObserver.h"
#include "ISaveable.h"

namespace Roguelike
{
class ArmorSave
{
    friend class ArmorComponent;
    float maxArmorPoints;
    float currentArmorPoints;
    float damageReduction;
};

class ArmorComponent : public GameEngine::Component,
                       public GameEngine::IObservable,
                       public ISaveable<ArmorComponent, ArmorSave>
{
  public:
    struct Parameters
    {
        float maxArmorPoints;
        float damageReduction;
    };
    static const Parameters defaultParameters;

    explicit ArmorComponent(GameEngine::GameObject *gameObject,
                            const ArmorComponent::Parameters &parameters = defaultParameters);

    void Update(float deltaTime) override;

    bool IsNotBroken() const;
    float GetCurrentArmorPoints() const;
    float GetDamageReduction() const;
    float GetMaxArmorPoints() const;
    virtual float ApplyDamage(const float damageAmount);
    virtual float IncreaseArmorPoints(const float armorPointAmount);
    void SetCurrentArmorPoints(const float newCurrentArmorPoints);
    void SetDamageReduction(const float newDamageReduction);
    void SetMaxArmorPoints(const float newMaxArmorPoints);

  protected:
    float maxArmorPoints;
    float currentArmorPoints;
    float damageReduction;

  private:
    friend class ISaveable<ArmorComponent, ArmorSave>;

    void LoadImpl(std::shared_ptr<const ArmorSave> save);
    void SaveImpl(std::shared_ptr<ArmorSave> save) const;
};
} // namespace Roguelike
