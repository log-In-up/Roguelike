#include "LevelManager.h"

#include <memory>
#include <vector>

#include "GameLevel.h"
#include "IObserver.h"
#include "InputComponent.h"
#include "LevelCompleteCondition.h"
#include "Settings.h"

namespace Roguelike
{
std::shared_ptr<LevelManager> LevelManager::Instance()
{
    static std::shared_ptr<LevelManager> instance(new LevelManager(), [](LevelManager *) {});
    return instance;
}

void LevelManager::Notify(std::shared_ptr<GameEngine::IObservable> observable)
{
    if (auto input = std::dynamic_pointer_cast<GameEngine::InputComponent>(observable))
    {
        if (input->GetLevelTransfer())
        {
            CheckConditions();
        }
    }
}

std::vector<std::shared_ptr<LevelCompleteCondition>> &LevelManager::GetCompleteConditions()
{
    return conditions;
}

void LevelManager::LoadNextLevel()
{
    conditions.clear();
    if (nextLevelNum >= gameLevelParameters.size())
    {
        GenerateLevel();
    }
    if (currentLevel)
    {
        playerData = currentLevel->GetPlayer()->Save();
        currentLevel->Stop();
    }

    auto levelParameters = gameLevelParameters[nextLevelNum];
    currentLevel = std::make_shared<GameLevel>(levelParameters);
    currentLevel->Start();
    for (const auto &condition : levelParameters.completeConditions)
    {
        conditions.emplace_back(LevelCompleteCondition::CreateCondition(currentLevel, condition));
        conditions.back()->Init();
    }

    if (playerData)
    {
        currentLevel->GetPlayer()->Load(playerData);
    }

    ++nextLevelNum;
}

void Roguelike::LevelManager::RegisterLevel(const GameLevel::Parameters &parameters)
{
    gameLevelParameters.emplace_back(parameters);
}

void LevelManager::CheckConditions()
{
    bool isConditionsReached = true;
    for (const auto &condition : conditions)
    {
        if (!condition->Completed())
        {
            isConditionsReached = false;
            break;
        }
    }
    if (isConditionsReached)
    {
        LoadNextLevel();
    }
}

void LevelManager::GenerateLevel()
{
    GameLevel::Parameters newLevelParameters = Settings::Instance()->firstLevelParameters;
    auto param = gameLevelParameters.rbegin();

    if (param != gameLevelParameters.rend())
    {
        newLevelParameters = *param;
        newLevelParameters.builderParameters.height += levelSizeIncrease;
        newLevelParameters.builderParameters.width += levelSizeIncrease;
        newLevelParameters.builderParameters.randSeed = -1;
        newLevelParameters.enemyCount += enemiesSizeIncrease;
    }
    gameLevelParameters.push_back(newLevelParameters);
}
} // namespace Roguelike