#pragma once
#include <GameWorld.h>
#include <Vector.h>
#include <Trigger.h>
#include <functional>

namespace Roguelike
{
	class LevelExit
	{
	private:
		GameEngine::GameObject* gameObject;
	public:
		LevelExit(GameEngine::Vector2Df& position);

		GameEngine::GameObject& GetGameObject()
		{
			return *gameObject;
		}
	};
}