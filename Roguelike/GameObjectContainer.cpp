#include "GameObjectContainer.h"

#include <string>

#include "GameObject.h"
#include "GameWorld.h"

namespace Roguelike
{
GameObjectContainer::GameObjectContainer()
{
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject();
}

GameObjectContainer::GameObjectContainer(std::string objectName)
{
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject(objectName);
}

GameEngine::GameObject *GameObjectContainer::GetGameObject()
{
    return gameObject;
}
} // namespace Roguelike