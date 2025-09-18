#pragma once
#include <string>

#include "GameObjectContainer.h"

namespace Roguelike
{
class LabyrinthElement : public GameObjectContainer
{
  public:
    explicit LabyrinthElement(const std::string &name) : GameObjectContainer(name) {};
};
} // namespace Roguelike
