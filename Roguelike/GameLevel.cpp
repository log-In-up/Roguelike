#include "GameLevel.h"

#include <memory>
#include <vector>

#include "AIActorManagerSystem.h"
#include "GameWorld.h"
#include "Labyrinth.h"
#include "LabyrinthBuilder.h"
#include "PlayerActor.h"
#include "Settings.h"
#include "Vector.h"

namespace Roguelike
{
GameLevel::GameLevel(const Parameters &parameters) : parameters(parameters) {};

void GameLevel::Restart()
{
    Stop();
    Start();
}

void GameLevel::Start()
{
    const auto *settings = Settings::Instance();

    auto builder = std::make_unique<LabyrinthBuilder>();
    builder->Generate(parameters.builderParameters);
    labyrinth = builder->ConstructLabyrinth();
    parameters.builderParameters.randSeed = builder->GetUsedSeed();

    std::vector<GameEngine::Vector2Df> generationDeadEnds;
    for (const auto &deadEnd : labyrinth->GetGenerationDeadEnds())
    {
        generationDeadEnds.push_back(labyrinth->GetCellCoordinates(deadEnd));
    }

    auto spawner = AIActorManagerSystem::Instance();
    spawner->Reset(labyrinth->GetLabyrinthCoodinatesRect());
    spawner->SpawnRandomly(settings->aiParameters, generationDeadEnds, parameters.enemyCount);

    auto startCell = labyrinth->GetCellCoordinates(labyrinth->GetStartCell());
    player = std::make_shared<PlayerActor>(settings->playerParameters, startCell);
}

void GameLevel::Stop()
{
    player = nullptr;
    labyrinth = nullptr;
    GameEngine::GameWorld::Instance()->Clear();
}

std::shared_ptr<Labyrinth> GameLevel::GetLabyrinth()
{
    return labyrinth;
}

std::shared_ptr<PlayerActor> GameLevel::GetPlayer()
{
    return player;
}
} // namespace Roguelike