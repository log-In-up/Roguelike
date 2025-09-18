#pragma once
#include "LabyrinthElement.h"
#include "Vector.h"

namespace Roguelike
{
class Floor : public LabyrinthElement
{
  public:
    Floor(GameEngine::Vector2Df position, int textureIndex, GameEngine::Vector2Di size);
};
} // namespace Roguelike
