#pragma once
#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "IObserver.h"

namespace Roguelike
{
class AITargetSelector : public GameEngine::Component,
                         virtual public GameEngine::IObservable,
                         virtual public GameEngine::IObserver
{
  public:
    explicit AITargetSelector(GameEngine::GameObject *gameObject);

    void Notify(std::shared_ptr<GameEngine::IObservable> observable) override;
    void Update(float deltaTime) override;

    void UpdateTarget();
};
} // namespace Roguelike
