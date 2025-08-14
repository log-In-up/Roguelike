#pragma once
#include <AudioComponent.h>
#include <GameObject.h>
#include <GameWorld.h>
#include <ResourceSystem.h>

namespace Roguelike
{
	class Music
	{
	public:
		Music(const std::string& soundName);
	private:
		GameEngine::GameObject* gameObject;
	};
}