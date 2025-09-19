#include "pch.h"

#include "IFixedUpdateSystem.h"

#include "GameWorld.h"

namespace GameEngine
{
IFixedUpdateSystem::IFixedUpdateSystem()
{
    GameWorld::Instance()->RegisterFixedUpdateSytem(this);
}

IFixedUpdateSystem::~IFixedUpdateSystem()
{
    GameWorld::Instance()->UnRegisterFixedUpdateSytem(this);
}

float IFixedUpdateSystem::GetFixedUpdateTime() const
{
    return fixedUpdateTime;
}

void IFixedUpdateSystem::SetFixedUpdateTime(const float newFixedUpdateTime)
{
    fixedUpdateTime = newFixedUpdateTime;
}
} // namespace GameEngine