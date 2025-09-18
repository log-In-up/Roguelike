#pragma once
#include <memory>

#include "AttackComponent.h"
#include "GameObject.h"
#include "IObserver.h"

namespace Roguelike
{
class PlayerAttackComponent : public AttackComponent, public GameEngine::IObserver
{
  public:
    explicit PlayerAttackComponent(
        GameEngine::GameObject *gameObject, const Parameters &atackParameters = defaultParameters,
        std::weak_ptr<GameEngine::GameObject> target = std::weak_ptr<GameEngine::GameObject>());

    virtual void Notify(std::shared_ptr<GameEngine::IObservable> observable) override;
};
} // namespace Roguelike
