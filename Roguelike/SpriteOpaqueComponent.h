#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "GameObject.h"
#include "IRenderable.h"
#include "OpaqueComponent.h"

namespace Roguelike
{
class SpriteOpaqueComponent : public OpaqueComponent, public GameEngine::IRenderable
{
  public:
    explicit SpriteOpaqueComponent(GameEngine::GameObject *gameObject, const int layer = 0);
    ~SpriteOpaqueComponent();

    void Render() override;
    void Update(float deltaTime) override;

  private:
    const sf::Sprite *sprite;
};
} // namespace Roguelike
