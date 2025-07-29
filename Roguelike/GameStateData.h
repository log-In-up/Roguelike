#pragma once
#include <SFML/Graphics.hpp>

#include "Memento.h"

namespace Arkanoid
{
	class GameStateData
	{
	public:
		virtual ~GameStateData() = default;
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void GetStateData(Memento& memento) = 0;
		virtual void HandleWindowEvent(const sf::Event& event) = 0;
		virtual void Init() = 0;
		virtual void SetStateData(Memento& memento) = 0;
		virtual void Update(float timeDelta) = 0;
	};
}