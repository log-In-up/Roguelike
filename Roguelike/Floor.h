#pragma once
#include <GameWorld.h>
#include <SpriteRendererComponent.h>
#include <ResourceSystem.h>

#include "GameObject.h"

namespace Roguelike
{
	class Floor
	{
	public:
		Floor(const GameEngine::Vector2Df& position, int textureMapIndex);
	private:
		GameEngine::GameObject* gameObject;
	};
}