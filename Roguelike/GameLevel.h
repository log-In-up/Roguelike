#pragma once
#include <memory>
#include <vector>

#include "Labyrinth.h"
#include "LabyrinthBuilder.h"
#include "LevelCompleteCondition.h"
#include "PlayerActor.h"
#include "Scene.h"

namespace Roguelike
{
class GameLevel : public GameEngine::Scene
{
  public:
    struct Parameters
    {
        LabyrinthBuilder::Parameters builderParameters;
        std::vector<LevelCompleteCondition::Type> completeConditions;
        int enemyCount;
    };

    explicit GameLevel(const Parameters &parameters);

    void Restart() override;
    void Start() override;
    void Stop() override;

    std::shared_ptr<Labyrinth> GetLabyrinth();
    std::shared_ptr<PlayerActor> GetPlayer();

  private:
    Parameters parameters;
    std::shared_ptr<PlayerActor> player;
    std::shared_ptr<Labyrinth> labyrinth;
};
} // namespace Roguelike
