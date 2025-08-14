#include "Music.h"

namespace Roguelike
{
	Music::Music(const std::string& soundName) : gameObject(GameEngine::GameWorld::Instance()->CreateGameObject("Music: " + soundName))
	{
		//auto gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Music: " + soundName);
		auto music = gameObject->AddComponent<GameEngine::AudioComponent>();
		music->SetAudio(*GameEngine::ResourceSystem::Instance()->GetSound(soundName));
		music->SetLoop(true);
		music->Play();
	}
}