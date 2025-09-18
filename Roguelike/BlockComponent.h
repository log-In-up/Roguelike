#pragma once
#include <SFML/Graphics/Color.hpp>

#include "Component.h"
#include "IRenderable.h"
#include "Vector.h"

namespace Roguelike
{
class BlockComponent : public GameEngine::Component, public GameEngine::IRenderable
{
  public:
    struct Parameters
    {
        float damageReduction;
        float speedCoefficient;
        GameEngine::Vector2Df iconCenterOffset;
        float iconRadius;
        sf::Color iconColor;
    };
    explicit BlockComponent(GameEngine::GameObject *gameObject, const Parameters &parameters = defaultParameters,
                            const int layer = 0);

    void Render() override;
    void Update(float deltaTime) override;

    bool GetIsBlocking() const;
    float ApplyDamage(const float damage) const;

  private:
    const static Parameters defaultParameters;
    float damageReduction;
    float speedCoefficient;
    GameEngine::Vector2Df iconCenterOffset;
    float iconRadius;
    sf::Color iconColor;
    bool isBlocking = false;
};
} // namespace Roguelike
