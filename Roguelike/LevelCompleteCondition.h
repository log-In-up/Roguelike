#pragma once
#include <memory>
#include <string>

#include "Trigger.h"

namespace Roguelike
{
class GameLevel;

class LevelCompleteCondition
{
  public:
    enum class Type
    {
        ExitReached,
        AllEnemyKilled
    };

    LevelCompleteCondition(const std::shared_ptr<GameLevel> gameLevel, const std::string &conditionDescription);

    static std::shared_ptr<LevelCompleteCondition> CreateCondition(const std::shared_ptr<GameLevel> gameLevel,
                                                                   const Type type);

    virtual bool Completed() const = 0;
    virtual void Init();

    const std::string &GetDescription() const;

  protected:
    std::weak_ptr<GameLevel> gameLevel;
    std::string conditionDescription;
};

class ExitReached : public LevelCompleteCondition
{
  public:
    explicit ExitReached(std::shared_ptr<GameLevel> gameLevel,
                         const std::string &conditionDescription = "Reach level exit");

    bool Completed() const override;

    void CheckExited(GameEngine::Trigger trigger, bool onEnter);

  private:
    bool reached = false;
};

class EnemyKilled : public LevelCompleteCondition
{
  public:
    explicit EnemyKilled(std::shared_ptr<GameLevel> gameLevel,
                         const std::string &conditionDescription = "Kill all enemies");

    bool Completed() const override;
};
} // namespace Roguelike
