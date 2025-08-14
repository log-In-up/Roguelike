#pragma once
#include <GameWorld.h>
#include <ResourceSystem.h>

#include "GameObject.h"

namespace Roguelike
{
	class Wall
	{
	public:
		Wall(const GameEngine::Vector2Df position, int textureMapIndex);
	private:
		GameEngine::GameObject* gameObject;
	};
}