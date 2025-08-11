#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace GameEngine
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* gameObject);
		virtual ~Component();

		virtual void Render(sf::RenderWindow& window) = 0;
		virtual void Update(float deltaTime) = 0;

		GameObject* GetGameObject();
	protected:
		GameObject* gameObject;
	};
}