#pragma once
#include <SFML/Graphics/Rect.hpp>

#include "Component.h"

namespace Roguelike
{
class OpaqueComponent : public GameEngine::Component
{
  public:
    friend class PerceptionSystem;

    explicit OpaqueComponent(GameEngine::GameObject *gameObject);
    ~OpaqueComponent();

    void Update(float deltaTime) override;

  protected:
    sf::FloatRect bounds;
};
} // namespace Roguelike
