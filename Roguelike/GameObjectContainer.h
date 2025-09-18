#pragma once
#include <string>

#include "GameObject.h"

namespace Roguelike
{
class GameObjectContainer
{
  public:
    GameObjectContainer();
    explicit GameObjectContainer(std::string objectName);
    virtual ~GameObjectContainer() = default;

    GameEngine::GameObject *GetGameObject();

  protected:
    GameEngine::GameObject *gameObject;
};
} // namespace Roguelike
