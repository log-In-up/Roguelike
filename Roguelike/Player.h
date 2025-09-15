#pragma once
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"
#include "LevelDataSynchronizer.h"

namespace Roguelike
{
	class Player
	{
	public:
		Player(const GameEngine::Vector2Df& position, const PlayerData& data);

		PlayerData GetPlayerData();

		GameEngine::GameObject* GetGameObject()
		{
			return gameObject;
		}
	private:
		GameEngine::GameObject* gameObject;
	};
}