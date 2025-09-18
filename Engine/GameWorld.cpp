#include "pch.h"

#include "GameWorld.h"

#include <algorithm>
#include <memory>
#include <sstream>
#include <string>

#include "GameObject.h"
#include "Logger.h"

namespace GameEngine
{
GameWorld *GameWorld::Instance()
{
    static GameWorld world;
    return &world;
}

GameObject *GameWorld::CreateGameObject()
{
    auto newGameObject = std::make_shared<GameObject>();
    gameObjects.push_back(newGameObject);
    return newGameObject.get();
}

GameObject *GameWorld::CreateGameObject(std::string name)
{
    auto newGameObject = std::make_shared<GameObject>(name);
    gameObjects.push_back(newGameObject);
    return newGameObject.get();
}

void GameWorld::Clear()
{
    for (int i = static_cast<int>(gameObjects.size()) - 1; i >= 0; --i)
    {
        DestroyGameObject(gameObjects[i]);
    }
    for (auto system : fixedUpdateSystems)
    {
        system.second = 0.0F;
    }
}

void GameWorld::ClearImmediate()
{
    for (int i = static_cast<int>(gameObjects.size()) - 1; i >= 0; --i)
    {
        DestroyGameObjectImmediate(gameObjects[i]);
    }
    for (auto system : fixedUpdateSystems)
    {
        system.second = 0.0F;
    }
}

void GameWorld::DestroyGameObject(GameObject *gameObject)
{
    if (gameObject != nullptr)
    {
        markedToDestroyGameObjects.push_back(gameObject->shared_from_this());
    }
}

void GameWorld::DestroyGameObject(std::shared_ptr<GameObject> gameObject)
{
    markedToDestroyGameObjects.push_back(gameObject);
}

void GameWorld::FixedUpdate(float deltaTime)
{
    for (auto &system : fixedUpdateSystems)
    {
        system.second += deltaTime;
        if (system.second >= system.first->GetFixedUpdateTime())
        {
            system.first->Update();
            system.second -= system.first->GetFixedUpdateTime();
        }
    }
}

void GameWorld::LateUpdate()
{
    for (int i = static_cast<int>(markedToDestroyGameObjects.size()) - 1; i >= 0; --i)
    {
        DestroyGameObjectImmediate(markedToDestroyGameObjects[i]);
    }
}

void GameWorld::Print() const
{
    for (const auto &obj : gameObjects)
    {
        if (obj == nullptr)
        {
            continue;
        }
        if (obj->GetComponent<TransformComponent>()->GetParent() == nullptr)
        {
            obj->Print();
        }
    }
}

void GameWorld::RegisterFixedUpdateSytem(IFixedUpdateSystem *system)
{
    fixedUpdateSystems[system] = 0.0F;
}

void GameWorld::Render()
{
    for (auto &object : gameObjects)
    {
        object->Render();
    }
}

void GameWorld::UnRegisterFixedUpdateSytem(IFixedUpdateSystem *system)
{
    auto foundIt = fixedUpdateSystems.find(system);
    if (foundIt != fixedUpdateSystems.end())
    {
        fixedUpdateSystems.erase(foundIt);
    }
}

void GameWorld::Update(float deltaTime)
{
    for (auto &object : gameObjects)
    {
        object->Update(deltaTime);
    }
}

void GameWorld::DestroyGameObjectImmediate(std::shared_ptr<GameObject> gameObject)
{
    gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
                                     [gameObject](std::shared_ptr<GameObject> obj) { return obj == gameObject; }),
                      gameObjects.end());
    markedToDestroyGameObjects.erase(
        std::remove_if(markedToDestroyGameObjects.begin(), markedToDestroyGameObjects.end(),
                       [gameObject](std::shared_ptr<GameObject> obj) { return obj == gameObject; }),
        markedToDestroyGameObjects.end());

    std::ostringstream message;
    message << gameObject << " deleted";
    LOG_INFO(message.str());
}
} // namespace GameEngine