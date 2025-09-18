#pragma once
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "AIActor.h"
#include "Component.h"
#include "GameObject.h"
#include "IDelayedAction.h"
#include "IFixedUpdateSystem.h"
#include "IObserver.h"
#include "Rect.h"
#include "Vector.h"

namespace Roguelike
{
constexpr float AIActorManagerSystemUpdateTime = 4.0F;

class AIActorManagerSystem : public GameEngine::IFixedUpdateSystem, public GameEngine::IObserver
{
  public:
    class DelayedDeadAIActorDestroyerComponent : public GameEngine::Component,
                                                 public IDelayedAction,
                                                 public GameEngine::IObservable
    {
      public:
        explicit DelayedDeadAIActorDestroyerComponent(GameEngine::GameObject *gameObject);

        void Update(float deltaTime) override;

      protected:
        void FinalAction() override;
        void UpdateAction(float deltaTime) override;
    };

    static std::shared_ptr<AIActorManagerSystem> Instance();

    void Notify(std::shared_ptr<GameEngine::IObservable> observable) override;
    void Update() override;

    int GetAiActorsCount() const;
    std::shared_ptr<AIActor> SpawnActorAt(
        const AIActor::Parameters &actorParameters, const GameEngine::Vector2Df &position,
        const std::function<void(std::shared_ptr<AIActor>)> &postSpawnUpdate = nullptr);
    void Reset(const GameEngine::FloatRect &newGameArea);
    void Spawn(const AIActor::Parameters &actorParameters, const std::vector<GameEngine::Vector2Df> &spawnPositions,
               const int count, const std::function<void(std::shared_ptr<AIActor>)> &postSpawnUpdate = nullptr);
    void SpawnRandomly(const AIActor::Parameters &actorParameters,
                       const std::vector<GameEngine::Vector2Df> &spawnPositions, const int count,
                       const std::function<void(std::shared_ptr<AIActor>)> &postSpawnUpdate = nullptr,
                       const int randSeed = -1);

  private:
    AIActorManagerSystem()
    {
        fixedUpdateTime = AIActorManagerSystemUpdateTime;
    };
    ~AIActorManagerSystem() {};

    AIActorManagerSystem(AIActorManagerSystem const &) = delete;
    AIActorManagerSystem &operator=(AIActorManagerSystem const &) = delete;
    std::map<std::weak_ptr<GameEngine::GameObject>, GameEngine::Vector2Df,
             std::owner_less<std::weak_ptr<GameEngine::GameObject>>>
        aIActors;
    GameEngine::FloatRect gameArea = {-1, -1, -1, -1};

    int aIActorsCount = 0;
};
} // namespace Roguelike
