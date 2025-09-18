#pragma once
#include <SFML/Graphics/Color.hpp>

#include "Component.h"
#include "GameObject.h"
#include "IRenderable.h"
#include "Vector.h"

namespace Roguelike
{
class BarComponent : public GameEngine::Component, public GameEngine::IRenderable
{
  public:
    struct Parameters
    {
        GameEngine::Vector2Df centerOffset;
        GameEngine::Vector2Df barSize;
        sf::Color barColor;
        float borderSize;
        float maxAmount = 0.0F;
    };
    explicit BarComponent(GameEngine::GameObject *gameObject, const Parameters &parameters = defaultBarParameters,
                          const int renderLayer = 0);

    void Render() override;
    void Update(float deltaTime) override = 0;

    float GetBorderSize() const;
    float GetCurrentAmount() const;
    float GetMaxAmount() const;
    GameEngine::Vector2Df GetBarSize() const;
    GameEngine::Vector2Df GetCenterOffset() const;
    sf::Color GetBarColor() const;
    void SetBarColor(const sf::Color newBarColor);
    void SetBarSize(const GameEngine::Vector2Df &newBarSize);
    void SetBorderSize(const float newBorderSize);
    void SetCenterOffset(const GameEngine::Vector2Df &newCenterOffset);
    void SetCurrentAmount(const float newCurrentAmount);
    void SetMaxAmount(const float newMaxAmount);

  protected:
    const static Parameters defaultBarParameters;
    GameEngine::Vector2Df centerOffset;
    GameEngine::Vector2Df barSize;
    sf::Color barColor;
    float maxAmount;
    float currentAmount;
    float borderSize;
};
} // namespace Roguelike
