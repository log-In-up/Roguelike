#pragma once
#include <SFML/Graphics.hpp>

namespace GameEngine
{
	class ColliderComponent;

	struct Collision
	{
	private:
		ColliderComponent* first;
		ColliderComponent* second;
		sf::FloatRect collisionRect;
	public:
		Collision(ColliderComponent* newFirst, ColliderComponent* newSecond, sf::FloatRect newCollisionRect) :
			first(newFirst), second(newSecond), collisionRect(newCollisionRect)
		{
		};
	};
}