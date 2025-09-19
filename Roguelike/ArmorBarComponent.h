#pragma once
#include <memory>

#include "ArmorComponent.h"
#include "BarComponent.h"
#include "GameObject.h"
#include "IObserver.h"

namespace Roguelike
{
class ArmorBarComponent : public BarComponent,
                          public GameEngine::IObserver,
                          public std::enable_shared_from_this<ArmorBarComponent>
{
  public:
    explicit ArmorBarComponent(GameEngine::GameObject *gameObject, const Parameters &parameters = defaultBarParameters,
                               const int layer = 0);

    void Notify(std::shared_ptr<GameEngine::IObservable> observable) override;
    void Render() override;
    void Update(float deltaTime) override;

    std::weak_ptr<ArmorComponent> GetArmorComponent() const;
    void SetArmorComponent(std::shared_ptr<ArmorComponent> newArmorComponent);

  protected:
    std::weak_ptr<ArmorComponent> armorComponent;
};
} // namespace Roguelike
