#include "OpaqueComponent.h"

#include "Component.h"
#include "GameObject.h"
#include "PerceptionSystem.h"

namespace Roguelike
{
OpaqueComponent::OpaqueComponent(GameEngine::GameObject *gameObject) : Component(gameObject)
{
    PerceptionSystem::Instance()->RegisterOpaqueComponent(this);
}

OpaqueComponent::~OpaqueComponent()
{
    PerceptionSystem::Instance()->UnregisterOpaqueComponent(this);
}

void OpaqueComponent::Update(float deltaTime)
{
}
} // namespace Roguelike