#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "ColliderComponent.h"
#include "GameObject.h"
#include "IRenderable.h"

namespace GameEngine
{
class SpriteColliderComponent : public ColliderComponent, public IRenderable
{
  public:
    explicit SpriteColliderComponent(GameObject *gameObject, int renderLayer = 0);
    ~SpriteColliderComponent();

    void Render() override;
    void Update(float deltaTime) override;

  private:
    const sf::Sprite *sprite;
};
} // namespace GameEngine
