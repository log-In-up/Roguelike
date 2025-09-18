#include "Wall.h"

#include "LabyrinthElement.h"
#include "ResourceSystem.h"
#include "RigidBodyComponent.h"
#include "Settings.h"
#include "SpriteColliderComponent.h"
#include "SpriteOpaqueComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike
{
Wall::Wall(const GameEngine::Vector2Df position, int textureIndex, const GameEngine::Vector2Di size)
    : LabyrinthElement("Wall")
{
    auto *transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto spriteRenderer =
        gameObject->AddComponent<GameEngine::SpriteRendererComponent>(static_cast<int>(Settings::RenderLayers::Walls));
    spriteRenderer->SetTexture(
        *GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("WallTextures", textureIndex));
    spriteRenderer->SetPixelSize(size.x, size.y);

    auto body = gameObject->AddComponent<GameEngine::RigidBodyComponent>();
    body->SetKinematic(true);

    gameObject->AddComponent<GameEngine::SpriteColliderComponent>(static_cast<int>(Settings::RenderLayers::Debug));

    gameObject->AddComponent<SpriteOpaqueComponent>(static_cast<int>(Settings::RenderLayers::Debug));
}
} // namespace Roguelike