#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Component.h"
#include "IRenderable.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace GameEngine
{
class SpriteRendererComponent : public Component, public IRenderable
{
  public:
    explicit SpriteRendererComponent(GameObject *gameObject, const int layer = 0);
    ~SpriteRendererComponent();

    void Render() override;
    void Update(float deltaTime) override;

    bool IsTextureRightDirected() const;
    const sf::Sprite *GetSprite() const;
    void FlipX(bool flip);
    void FlipY(bool flip);
    void SetColor(const sf::Color newColor);
    void SetPixelSize(const Vector2Di &size);
    void SetPixelSize(int newWidth, int newHeight);
    void SetTexture(const sf::Texture &newTexture, const bool newIsTextureRightDirected = true);

  private:
    Vector2Df scale;
    sf::Sprite *sprite;
    TransformComponent *transform;

    bool isFlipX = false;
    bool isFlipY = false;
    bool isTextureRightDirected = true;
};
} // namespace GameEngine
