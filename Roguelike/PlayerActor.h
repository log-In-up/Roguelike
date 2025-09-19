#pragma once
#include "Actor.h"
#include "Vector.h"

namespace Roguelike
{
class PlayerActor : public Actor
{
  public:
    explicit PlayerActor(const Actor::Parameters &parameters, const GameEngine::Vector2Df &position = {0.0F, 0.0F});
};
} // namespace Roguelike
