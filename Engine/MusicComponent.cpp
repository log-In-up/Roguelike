#include "pch.h"

#include "MusicComponent.h"

#include "Component.h"
#include "GameObject.h"

namespace GameEngine
{
MusicComponent::MusicComponent(GameObject *gameObject) : Component(gameObject)
{
}

MusicComponent::~MusicComponent()
{
    music->stop();
}

void MusicComponent::Update(float deltaTime)
{
}

void MusicComponent::Pause()
{
    music->pause();
}

void MusicComponent::Play()
{
    if (music->getStatus() != sf::Music::Playing)
    {
        music->play();
    }
}

void MusicComponent::Resume()
{
    if (music->getStatus() != sf::Music::Playing)
    {
        music->play();
    }
}

void MusicComponent::SetLoop(bool newLoop)
{
    music->setLoop(newLoop);
}

void MusicComponent::SetMusic(sf::Music *newMusic)
{
    music = newMusic;
}

void MusicComponent::SetVolume(float volume)
{
    music->setVolume(volume);
}

void MusicComponent::Stop()
{
    music->stop();
}
} // namespace GameEngine