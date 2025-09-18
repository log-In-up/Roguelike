#pragma once
#include <SFML/Graphics/Rect.hpp>

namespace GameEngine
{
class ColliderComponent;

struct Collision
{
  public:
    Collision(ColliderComponent *first, ColliderComponent *second, sf::FloatRect collisionRect)
        : first(first), second(second), collisionRect(collisionRect) {};

    ColliderComponent *first;
    ColliderComponent *second;
    sf::FloatRect collisionRect;
};
} // namespace GameEngine