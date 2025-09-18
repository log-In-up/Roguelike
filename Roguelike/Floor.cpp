#include "Floor.h"

#include "LabyrinthElement.h"
#include "ResourceSystem.h"
#include "Settings.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike
{
Floor::Floor(GameEngine::Vector2Df position, int textureIndex, GameEngine::Vector2Di size) : LabyrinthElement("Floor")
{
    auto *transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto sprite =
        gameObject->AddComponent<GameEngine::SpriteRendererComponent>(static_cast<int>(Settings::RenderLayers::Floor));
    sprite->SetTexture(
        *GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("FloorTextures", textureIndex));
    sprite->SetPixelSize(size.x, size.y);
}
} // namespace Roguelike