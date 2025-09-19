#include "ActorComponent.h"

#include "ActorRegisterSystem.h"
#include "Component.h"
#include "GameObject.h"
#include "Logger.h"

namespace Roguelike
{
ActorComponent::ActorComponent(GameEngine::GameObject *gameObject, int groupID)
    : Component(gameObject), groupID(groupID)
{
    if (gameObject->GetComponent<ActorComponent>() != nullptr)
    {
        LOG_WARN("Already have ActorComponent!");
        return;
    }
    ActorRegisterSystem::Instance()->Register(this);
}

ActorComponent::~ActorComponent()
{
    ActorRegisterSystem::Instance()->UnRegister(this);
}

void ActorComponent::Update(float deltaTime)
{
}

int ActorComponent::GetGroupID() const
{
    return groupID;
}

void ActorComponent::SetGroupID(const int newGroupID)
{
    groupID = newGroupID;
}
} // namespace Roguelike