#pragma once
#include <vector>

#include "AITypedBlackboardComponent.h"
#include "GameObject.h"
#include "Vector.h"

namespace Roguelike
{
using AIBlackboard =
    GameEngine::AITypedBlackboardComponent<bool, float, GameEngine::Vector2Df, GameEngine::GameObject *,
                                           std::vector<GameEngine::GameObject *> *>;
}
