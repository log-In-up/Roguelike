#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Component.h"

namespace GameEngine
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent(GameObject* gameObject);
		~AudioComponent();

		void Pause();
		void Play();
		void Render(sf::RenderWindow& window) override;
		void Resume();
		void SetAudio(const sf::SoundBuffer& audio);
		void SetLoop(bool loop);
		void SetVolume(float volume);
		void Stop();
		void Update(float deltaTime) override;
	private:
		sf::Sound* sound;
	};
}
