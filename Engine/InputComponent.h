#pragma once
#include <SFML/Window.hpp>

#include "Component.h"

namespace GameEngine
{
	class InputComponent : public Component
	{
	private:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;
	public:
		InputComponent(GameObject* gameObject);

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;
		void Render(sf::RenderWindow& window) override;
		void Update(float deltaTime) override;
	};
}