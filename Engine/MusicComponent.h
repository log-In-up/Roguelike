#pragma once
#include <SFML/Audio/Music.hpp>

#include "Component.h"

namespace GameEngine
{
class MusicComponent : public Component
{
  public:
    explicit MusicComponent(GameObject *gameObject);
    ~MusicComponent();

    void Update(float deltaTime) override;

    void Pause();
    void Play();
    void Resume();
    void SetLoop(bool newLoop);
    void SetMusic(sf::Music *newMusic);
    void SetVolume(float volume);
    void Stop();

  private:
    sf::Music *music = nullptr;
};
} // namespace GameEngine
