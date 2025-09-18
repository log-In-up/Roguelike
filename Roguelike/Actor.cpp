#include "Actor.h"

#include <memory>

#include "ActorComponent.h"
#include "ActorMovementComponent.h"
#include "ActorSpriteDirectionComponent.h"
#include "ArmorBarComponent.h"
#include "ArmorComponent.h"
#include "BlockComponent.h"
#include "GameObjectContainer.h"
#include "HealthBarComponent.h"
#include "HealthComponent.h"
#include "ISaveable.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "Settings.h"
#include "SpriteAnimationComponent.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike
{
Actor::Actor(const Parameters &parameters, const GameEngine::Vector2Df &position)
    : GameObjectContainer(parameters.actorName)
{
    auto *transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);
    gameObject->AddComponent<ActorComponent>(parameters.actorGroupID);

    auto healthComponent = gameObject->AddComponent<HealthComponent>(parameters.maxHealthAmount);
    auto healthBar = gameObject->AddComponent<HealthBarComponent>(parameters.healthBarParameters,
                                                                  static_cast<int>(Settings::RenderLayers::UI1));
    healthBar->SetHealthComponent(healthComponent);

    const auto &defaultAnimation = parameters.animations.at(parameters.defaultAnimationName);
    const auto *texture =
        GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared(defaultAnimation.textureMapName, 0);
    auto render =
        gameObject->AddComponent<GameEngine::SpriteRendererComponent>(static_cast<int>(Settings::RenderLayers::Actors));
    render->SetTexture(*texture);
    render->SetPixelSize(parameters.spriteSize);

    auto animationComponent = gameObject->AddComponent<GameEngine::SpriteAnimationComponent>();
    for (const auto &animationPair : parameters.animations)
    {
        animationComponent->AddAnimation(animationPair.first, animationPair.second,
                                         animationPair.first == parameters.defaultAnimationName);
    }
    gameObject->AddComponent<ActorSpriteDirectionComponent>();

    gameObject->AddComponent<ActorMovementComponent>(parameters.movementSpeed);
    gameObject->AddComponent<GameEngine::RigidBodyComponent>();
    gameObject->AddComponent<GameEngine::SpriteColliderComponent>(static_cast<int>(Settings::RenderLayers::Debug));

    if (parameters.haveBlock)
    {
        gameObject->AddComponent<BlockComponent>(parameters.blockParameters,
                                                 static_cast<int>(Settings::RenderLayers::UI2));
    }
    if (parameters.haveArmor)
    {
        auto armorComponent = gameObject->AddComponent<ArmorComponent>(parameters.armorParameters);
        auto armorBar = gameObject->AddComponent<ArmorBarComponent>(parameters.armorBarParameters,
                                                                    static_cast<int>(Settings::RenderLayers::UI1));
        armorBar->SetArmorComponent(armorComponent);
    }
}

void Actor::LoadImpl(std::shared_ptr<const ActorSave> save)
{
    if (auto *healthComponent = gameObject->GetComponent<HealthComponent>())
    {
        healthComponent->Load(save->healthSave);
    }
    if (auto *armorComponent = gameObject->GetComponent<ArmorComponent>())
    {
        armorComponent->Load(save->armorSave);
    }
    if (auto *actorComponent = gameObject->GetComponent<ActorComponent>())
    {
        actorComponent->SetGroupID(save->actorGroupID);
    }
}

void Actor::SaveImpl(std::shared_ptr<ActorSave> save) const
{
    if (auto *healthComponent = gameObject->GetComponent<HealthComponent>())
    {
        save->healthSave = healthComponent->Save();
    }
    if (auto *armorComponent = gameObject->GetComponent<ArmorComponent>())
    {
        save->armorSave = armorComponent->Save();
    }
    if (auto *actorComponent = gameObject->GetComponent<ActorComponent>())
    {
        save->actorGroupID = actorComponent->GetGroupID();
    }
}
} // namespace Roguelike