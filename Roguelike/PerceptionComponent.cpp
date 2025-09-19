#include "PerceptionComponent.h"

#include <vector>

#include "ActorRegisterSystem.h"
#include "Component.h"
#include "Logger.h"
#include "PerceptionSystem.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike
{
PerceptionComponent::PerceptionComponent(GameEngine::GameObject *gameObject, const Parameters &parameters)
    : Component(gameObject),
      visionDirection(GameEngine::Vector2Df(parameters.visionDirectionX, parameters.visionDirectionY)),
      visionAngle(parameters.visionAngle), visionRadius(parameters.visionRadius), senseRadius(parameters.senseRadius)
{
    transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    PerceptionSystem::Instance()->RegisterPerceptionComponent(this);
}

PerceptionComponent::~PerceptionComponent()
{
    PerceptionSystem::Instance()->UnregisterPerceptionComponent(this);
}

void PerceptionComponent::Update(float deltaTime)
{
}

const GameEngine::TransformComponent *PerceptionComponent::GetTransform() const
{
    return transform;
}

const GameEngine::Vector2Df &PerceptionComponent::GetVisionDirection() const
{
    return visionDirection;
}

const std::vector<GameEngine::GameObject *> *PerceptionComponent::GetDetectedActors()
{
    return &detectedActors;
}

float PerceptionComponent::GetSenseRadius() const
{
    return senseRadius;
}

float PerceptionComponent::GetVisionAngle() const
{
    return visionAngle;
}

float PerceptionComponent::GetVisionRadius() const
{
    return visionRadius;
}

void PerceptionComponent::SetSenseRadius(const float newSenseRadius)
{
    senseRadius = newSenseRadius;
}

void PerceptionComponent::SetVisionAngle(const float newVisionAngle)
{
    visionAngle = newVisionAngle;
}

void PerceptionComponent::SetVisionDirection(const GameEngine::Vector2Df &newVisionDirection)
{
    if (newVisionDirection.GetLength() > 0.0F)
    {
        visionDirection = Normalized(newVisionDirection);
    }
    else
    {
        LOG_WARN("vision direction must not be zero vector");
    }
}

void PerceptionComponent::SetVisionRadius(const float newVisionRadius)
{
    visionRadius = newVisionRadius;
}

void PerceptionComponent::UpdateDetectedActors()
{
    const auto &actors = ActorRegisterSystem::Instance()->GetActorsList();
    UpdateDetectedActors(actors);
}

void PerceptionComponent::UpdateDetectedActors(const std::vector<GameEngine::GameObject *> &actors)
{
    detectedActors.clear();
    for (const auto &actor : actors)
    {
        if (actor != gameObject && PerceptionSystem::Instance()->CanDetect(this, actor))
        {
            detectedActors.push_back(actor);
        }
    }
    Emit();
}
} // namespace Roguelike