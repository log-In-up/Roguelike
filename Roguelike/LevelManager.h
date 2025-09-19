#pragma once
#include <memory>
#include <vector>

#include "Actor.h"
#include "GameLevel.h"
#include "IObserver.h"
#include "LevelCompleteCondition.h"

namespace Roguelike
{
class LevelManager : public GameEngine::IObserver
{
  public:
    static std::shared_ptr<LevelManager> Instance();

    void Notify(std::shared_ptr<GameEngine::IObservable> observable) override;

    std::vector<std::shared_ptr<LevelCompleteCondition>> &GetCompleteConditions();
    void LoadNextLevel();
    void RegisterLevel(const GameLevel::Parameters &parameters);

  private:
    void CheckConditions();
    void GenerateLevel();

    LevelManager() = default;
    ~LevelManager() = default;
    LevelManager(const LevelManager &) = delete;
    LevelManager operator=(const LevelManager &) = delete;

    std::vector<GameLevel::Parameters> gameLevelParameters;
    std::shared_ptr<GameLevel> currentLevel;
    std::vector<std::shared_ptr<LevelCompleteCondition>> conditions;
    std::shared_ptr<ActorSave> playerData;
    const int levelSizeIncrease = 4;
    const int enemiesSizeIncrease = 0;
    int nextLevelNum = 0;
};
} // namespace Roguelike
