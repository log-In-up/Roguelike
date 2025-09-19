#include "ActorRegisterSystem.h"

#include <algorithm>
#include <sstream>
#include <vector>

#include "ActorComponent.h"
#include "GameObject.h"
#include "Logger.h"

namespace Roguelike
{
ActorRegisterSystem *ActorRegisterSystem::Instance()
{
    static ActorRegisterSystem instance;
    return &instance;
}

const std::vector<GameEngine::GameObject *> &ActorRegisterSystem::GetActorsList()
{
    return actors;
}

std::vector<GameEngine::GameObject *> ActorRegisterSystem::GetActorsInGroupList(const int groupID)
{
    std::vector<GameEngine::GameObject *> actorsList;
    for (auto &actor : actors)
    {
        auto *actorComponent = actor->GetComponent<ActorComponent>();
        if (actorComponent->GetGroupID() == groupID)
        {
            actorsList.push_back(actor);
        }
    }
    return actorsList;
}

std::vector<GameEngine::GameObject *> ActorRegisterSystem::GetActorsNotInGroupList(const int groupID)
{
    std::vector<GameEngine::GameObject *> actorsList;
    for (auto &actor : actors)
    {
        auto *actorComponent = actor->GetComponent<ActorComponent>();
        if (actorComponent->GetGroupID() != groupID)
        {
            actorsList.push_back(actor);
        }
    }
    return actorsList;
}

void ActorRegisterSystem::Register(ActorComponent *actor)
{
    auto *actorObject = actor->GetGameObject();
    auto actorRegistered = std::find(actors.begin(), actors.end(), actorObject);
    if (actorRegistered == actors.end())
    {
        actors.emplace_back(actorObject);
        std::ostringstream message;
        message << "Registered actor " << actorObject;
        LOG_INFO(message.str());
    }
    else
    {
        std::ostringstream message;
        message << actorObject << " already registered";
        LOG_WARN(message.str());
    }
}

void ActorRegisterSystem::UnRegister(ActorComponent *actor)
{
    auto *actorObject = actor->GetGameObject();
    actors.erase(std::remove_if(actors.begin(), actors.end(),
                                [actorObject](GameEngine::GameObject *obj) { return actorObject == obj; }),
                 actors.end());
}
} // namespace Roguelike