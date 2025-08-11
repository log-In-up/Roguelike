#pragma once
#include "GameObject.h"
#include "InputComponent.h"
#include "SpriteRendererComponent.h"

namespace GameEngine
{
	class SpriteDirectionComponent : public Component
	{
	private:
		InputComponent* input;
		SpriteRendererComponent* spriteRenderer;
	public:
		SpriteDirectionComponent(GameObject* gameObject);

		void Render(sf::RenderWindow& window) override;
		void Update(float deltaTime) override;
	};
}
