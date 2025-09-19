#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Component.h"

namespace GameEngine
{
class SoundComponent : public Component
{
  public:
    explicit SoundComponent(GameObject *gameObject);
    ~SoundComponent();

    void Update(float deltaTime) override;

    void Pause();
    void Play();
    void Resume();
    void SetLoop(bool newLoop);
    void SetSound(const sf::SoundBuffer &newSound);
    void SetVolume(float volume);
    void Stop();

  private:
    sf::Sound *sound;
};
} // namespace GameEngine
