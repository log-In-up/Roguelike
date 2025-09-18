#include "pch.h"

#include "SoundComponent.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Component.h"
#include "GameObject.h"

namespace GameEngine
{
SoundComponent::SoundComponent(GameObject *gameObject) : Component(gameObject)
{
    sound = new sf::Sound();
}

SoundComponent::~SoundComponent()
{
    sound->stop();
    delete sound;
}

void SoundComponent::Update(float deltaTime)
{
}

void SoundComponent::Pause()
{
    sound->pause();
}

void SoundComponent::Play()
{
    if (sound->getStatus() != sf::Sound::Playing)
    {
        sound->play();
    }
}

void SoundComponent::Resume()
{
    if (sound->getStatus() != sf::Sound::Playing)
    {
        sound->play();
    }
}

void SoundComponent::SetLoop(bool newLoop)
{
    sound->setLoop(newLoop);
}

void SoundComponent::SetSound(const sf::SoundBuffer &newSound)
{
    sound->setBuffer(newSound);
}

void SoundComponent::SetVolume(float volume)
{
    sound->setVolume(volume);
}

void SoundComponent::Stop()
{
    sound->stop();
}
} // namespace GameEngine