#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "BarComponent.h"
#include "BlockComponent.h"
#include "GameObjectContainer.h"
#include "HealthComponent.h"
#include "ISaveable.h"
#include "SpriteAnimationComponent.h"
#include "Vector.h"

namespace Roguelike
{
class ActorSave
{
    friend class Actor;
    std::shared_ptr<HealthSave> healthSave;
    std::shared_ptr<ArmorSave> armorSave;
    int actorGroupID = 0;
};

class Actor : public GameObjectContainer, public ISaveable<Actor, ActorSave>
{
  public:
    struct Parameters
    {
        int actorGroupID;
        float maxHealthAmount;
        BarComponent::Parameters healthBarParameters;
        float movementSpeed;
        GameEngine::Vector2Di spriteSize;
        std::string defaultAnimationName;
        std::unordered_map<std::string, GameEngine::Animation> animations;
        bool haveBlock;
        BlockComponent::Parameters blockParameters;
        bool haveArmor;
        ArmorComponent::Parameters armorParameters;
        BarComponent::Parameters armorBarParameters;
        AttackComponent::Parameters attackComponentParameters;
        std::string actorName = "Actor";
    };
    explicit Actor(const Parameters &parameters, const GameEngine::Vector2Df &position = {0.0F, 0.0F});

  private:
    friend class ISaveable<Actor, ActorSave>;
    void LoadImpl(std::shared_ptr<const ActorSave> save);
    void SaveImpl(std::shared_ptr<ActorSave> save) const;
};
} // namespace Roguelike
