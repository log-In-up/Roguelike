#pragma once
#include <vector>

#include "GameObject.h"
#include "IFixedUpdateSystem.h"
#include "Vector.h"

namespace Roguelike

{
class OpaqueComponent;
class PerceptionComponent;

class PerceptionSystem : public GameEngine::IFixedUpdateSystem
{
  public:
    static PerceptionSystem *Instance();

    void Update() override;

    bool CanDetect(PerceptionComponent *perceptionComponent, GameEngine::GameObject *target) const;
    bool LineClear(const GameEngine::Vector2Df &startPoint, const GameEngine::Vector2Df &endPoint) const;
    void Clear();
    void ClearOpaqueObjects();
    void ClearPerceptionComponents();
    void RegisterOpaqueComponent(OpaqueComponent *component);
    void RegisterPerceptionComponent(PerceptionComponent *component);
    void UnregisterOpaqueComponent(OpaqueComponent *component);
    void UnregisterPerceptionComponent(PerceptionComponent *component);

  private:
    std::vector<OpaqueComponent *> opaqueComponents;
    std::vector<PerceptionComponent *> perceptionComponents;

    PerceptionSystem() = default;
    ~PerceptionSystem() = default;
    PerceptionSystem(const PerceptionSystem &) = delete;
    PerceptionSystem &operator=(const PerceptionSystem &) = delete;
};
} // namespace Roguelike
