#pragma once
#include "LabyrinthElement.h"
#include "Vector.h"

namespace Roguelike
{
class Wall : public LabyrinthElement
{
  public:
    Wall(const GameEngine::Vector2Df position, int textureIndex, const GameEngine::Vector2Di size);
};
} // namespace Roguelike
