#include "AIActorManagerSystem.h"

#include <cstdlib>
#include <ctime>
#include <functional>
#include <memory>
#include <vector>

#include "AIActor.h"
#include "Component.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "IObserver.h"
#include "Settings.h"
#include "TransformComponent.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike
{
static const std::vector<GameEngine::Vector2Df> baseOffsets = {{0, 0}, {0, -1}, {0, 1},  {1, 0},  {1, -1},
                                                               {1, 1}, {-1, 0}, {-1, 1}, {-1, -1}};

AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent::DelayedDeadAIActorDestroyerComponent(
    GameEngine::GameObject *gameObject)
    : Component(gameObject)
{
}

void AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent::Update(float deltaTime)
{
    UpdateTimer(deltaTime);
}

void AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent::FinalAction()
{
    if (auto *healthComponent = gameObject->GetComponent<HealthComponent>())
    {
        if (healthComponent->IsAlive())
        {
            gameObject->RemoveComponent(this);
        }
        else
        {
            Emit();
            GameEngine::GameWorld::Instance()->DestroyGameObject(gameObject);
        }
    }
}

// NOLINTBEGIN(misc-unused-parameters) : overrided method with parameter
void AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent::UpdateAction(float deltaTime)
{
    if (auto *healthComponent = gameObject->GetComponent<HealthComponent>())
    {
        if (healthComponent->IsAlive())
        {
            gameObject->RemoveComponent(this);
        }
    }
}

std::shared_ptr<AIActorManagerSystem> AIActorManagerSystem::Instance()
{
    const static std::shared_ptr<AIActorManagerSystem> instance(new AIActorManagerSystem(),
                                                                [](AIActorManagerSystem *) {});
    return instance;
}

void AIActorManagerSystem::Notify(std::shared_ptr<GameEngine::IObservable> observable)
{
    auto healthComponent = std::dynamic_pointer_cast<HealthComponent>(observable);
    if (healthComponent)
    {
        if (healthComponent && !healthComponent->IsAlive())
        {
            auto delayedDestroyer =
                healthComponent->GetGameObject()->AddComponent<DelayedDeadAIActorDestroyerComponent>();
            delayedDestroyer->StartTimer(Settings::Instance()->timeToRemoveAfterDeath);
            delayedDestroyer->AddObserver(Instance());
        }
        return;
    }

    auto destroyer = std::dynamic_pointer_cast<AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent>(observable);
    if (destroyer)
    {
        --aIActorsCount;
    }
}

void AIActorManagerSystem::Update()
{
    for (auto actorIterator = aIActors.begin(); actorIterator != aIActors.end();)
    {
        if (actorIterator->first.expired())
        {
            actorIterator = aIActors.erase(actorIterator);
        }
        else
        {
            auto actor = actorIterator->first.lock();
            auto *transform = actor->GetComponent<GameEngine::TransformComponent>();
            if (!InRect(gameArea.topLeft, gameArea.GetSize(), transform->GetWorldPosition()))
            {
                transform->SetWorldPosition(actorIterator->second);
            }
            ++actorIterator;
        }
    }
}

int AIActorManagerSystem::GetAiActorsCount() const
{
    return aIActorsCount;
}

std::shared_ptr<AIActor> AIActorManagerSystem::SpawnActorAt(
    const AIActor::Parameters &actorParameters, const GameEngine::Vector2Df &position,
    const std::function<void(std::shared_ptr<AIActor>)> &postSpawnUpdate)
{
    auto actor = std::shared_ptr<AIActor>(new AIActor(actorParameters, position));
    if (postSpawnUpdate)
    {
        postSpawnUpdate(actor);
    }
    auto *healthComponent = actor->GetGameObject()->GetComponent<HealthComponent>();
    healthComponent->AddObserver(Instance());

    ++aIActorsCount;
    aIActors[actor->GetGameObject()->weak_from_this()] = position;
    return actor;
}

void AIActorManagerSystem::Reset(const GameEngine::FloatRect &newGameArea)
{
    aIActors.clear();
    aIActorsCount = 0;
    gameArea = newGameArea;
}

void AIActorManagerSystem::Spawn(const AIActor::Parameters &actorParameters,
                                 const std::vector<GameEngine::Vector2Df> &spawnPositions, const int count,
                                 const std::function<void(std::shared_ptr<AIActor>)> &postSpawnUpdate)
{
    const GameEngine::Vector2Df actorSize =
        GameEngine::Convert<GameEngine::Vector2Df>(actorParameters.baseActorParameters.spriteSize);

    std::vector<int> actorSpawnedAt(spawnPositions.size(), 0);
    for (int i = 0, positionNumber = 0; i < count; ++i, positionNumber = i % static_cast<int>(spawnPositions.size()))
    {
        const GameEngine::Vector2Df spawnPosition =
            spawnPositions[positionNumber] + actorSize * baseOffsets[actorSpawnedAt[positionNumber]];

        SpawnActorAt(actorParameters, spawnPosition, postSpawnUpdate);

        ++actorSpawnedAt[positionNumber];
    }
}

void AIActorManagerSystem::SpawnRandomly(const AIActor::Parameters &actorParameters,
                                         const std::vector<GameEngine::Vector2Df> &spawnPositions, const int count,
                                         const std::function<void(std::shared_ptr<AIActor>)> &postSpawnUpdate,
                                         const int randSeed)
{
    if (randSeed == -1)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }
    else
    {
        std::srand(randSeed);
    }
    const GameEngine::Vector2Df actorSize =
        GameEngine::Convert<GameEngine::Vector2Df>(actorParameters.baseActorParameters.spriteSize);

    std::vector<int> actorSpawnedAt(spawnPositions.size(), 0);
    for (int i = 0; i < count; ++i)
    {
        const int positionNumber = std::rand() % static_cast<int>(spawnPositions.size());

        const GameEngine::Vector2Df spawnPosition =
            spawnPositions[positionNumber] + actorSize * baseOffsets[actorSpawnedAt[positionNumber]];

        SpawnActorAt(actorParameters, spawnPosition, postSpawnUpdate);

        ++actorSpawnedAt[positionNumber];
    }
}
} // namespace Roguelike