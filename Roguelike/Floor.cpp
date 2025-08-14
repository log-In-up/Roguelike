#include "Floor.h"

using namespace GameEngine;

namespace Roguelike
{
	Floor::Floor(const Vector2Df& position, int textureMapIndex)
	{
		gameObject = GameWorld::Instance()->CreateGameObject("Floor");
		auto transform = gameObject->GetComponent<TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureMapElementShared("level_floors", textureMapIndex));
		renderer->SetPixelSize(128, 128);
	}
}