#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <MovementComponent.h>
#include <SpriteDirectionComponent.h>
#include <SpriteMovementAnimationComponent.h>
#include <StatsComponent.h>
#include <AttackComponent.h>

#include "Player.h"
#include "GameSettings.h"

namespace Roguelike
{
	Player::Player(const GameEngine::Vector2Df& position) : gameObject(GameEngine::GameWorld::Instance()->CreateGameObject("Player"))
	{
		auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
		renderer->SetTexture(*GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("player", 0));
		renderer->SetPixelSize(100, 100);

		auto camera = gameObject->AddComponent<GameEngine::CameraComponent>();
		camera->SetBaseResolution(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT);

		auto input = gameObject->AddComponent<GameEngine::InputComponent>();

		auto movement = gameObject->AddComponent<GameEngine::MovementComponent>();
		movement->SetSpeed(400.f);

		auto spriteDirection = gameObject->AddComponent<GameEngine::SpriteDirectionComponent>();

		auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();

		auto animator = gameObject->AddComponent<GameEngine::SpriteMovementAnimationComponent>();
		animator->Initialize("player", 6.f);

		auto statsComponent = gameObject->AddComponent<GameEngine::StatsComponent>(100.f, 50.f);

		auto attackComponent = gameObject->AddComponent<GameEngine::AttackComponent>(10.f);
	}
}