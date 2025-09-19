#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "GameObject.h"
#include "IFixedUpdateSystem.h"

namespace GameEngine
{
class GameWorld
{
  public:
    static GameWorld *Instance();

    GameObject *CreateGameObject();
    GameObject *CreateGameObject(std::string name);
    void Clear();
    void ClearImmediate();
    void DestroyGameObject(GameObject *gameObject);
    void DestroyGameObject(std::shared_ptr<GameObject> gameObject);
    void FixedUpdate(float deltaTime);
    void LateUpdate();
    void Print() const;
    void RegisterFixedUpdateSytem(IFixedUpdateSystem *system);
    void Render();
    void UnRegisterFixedUpdateSytem(IFixedUpdateSystem *system);
    void Update(float deltaTime);

  private:
    GameWorld() {};
    ~GameWorld() {};

    GameWorld(GameWorld const &) = delete;
    GameWorld &operator=(GameWorld const &) = delete;

    std::unordered_map<IFixedUpdateSystem *, float> fixedUpdateSystems;

    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::shared_ptr<GameObject>> markedToDestroyGameObjects;

    void DestroyGameObjectImmediate(std::shared_ptr<GameObject> gameObject);
};
} // namespace GameEngine
