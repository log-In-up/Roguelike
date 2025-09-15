#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

#include "LevelExit.h"
#include "GameSettings.h"

namespace Roguelike
{
	LevelExit::LevelExit(GameEngine::Vector2Df& position)
		: gameObject(GameEngine::GameWorld::Instance()->CreateGameObject("Exit"))
	{
		auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
		renderer->SetTexture(*GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("level_floors", 16));
		renderer->SetPixelSize((int)SETTINGS.SPRITE_SIZE, (int)SETTINGS.SPRITE_SIZE);

		auto spriteCollider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
		spriteCollider->SetTrigger(true);
	}
}