#pragma once
#include "Floor.h"
#include "Vector.h"

namespace Roguelike
{
class LabyrinthExit : public Floor
{
  public:
    LabyrinthExit(GameEngine::Vector2Df position, int textureIndex, GameEngine::Vector2Di size);
};
} // namespace Roguelike
