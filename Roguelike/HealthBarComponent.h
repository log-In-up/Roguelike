#pragma once
#include <memory>

#include <SFML/Graphics/Color.hpp>

#include "BarComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "IObserver.h"
#include "Vector.h"

namespace Roguelike
{
class HealthBarComponent : public BarComponent,
                           public GameEngine::IObserver,
                           public std::enable_shared_from_this<HealthBarComponent>
{
  public:
    explicit HealthBarComponent(GameEngine::GameObject *gameObject, const Parameters &parameters = defaultBarParameters,
                                const int renderLayer = 0);

    void Notify(std::shared_ptr<GameEngine::IObservable> observable) override;
    void Render() override;
    void Update(float deltTime) override;

    std::weak_ptr<HealthComponent> GetHealthComponent() const;
    void SetHealthComponent(std::shared_ptr<HealthComponent> newHealthComponent);

  protected:
    std::weak_ptr<HealthComponent> healthComponent;
};
} // namespace Roguelike
