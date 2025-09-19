#include "BackgroundMusic.h"

#include "GameObjectContainer.h"
#include "MusicComponent.h"
#include "ResourceSystem.h"

namespace Roguelike
{
BackgroundMusic::BackgroundMusic() : GameObjectContainer("Background music")
{
    auto music = gameObject->AddComponent<GameEngine::MusicComponent>();
    music->SetMusic(GameEngine::ResourceSystem::Instance()->GetMusicShared("background"));
    music->SetLoop(true);
    music->Play();
}
} // namespace Roguelike