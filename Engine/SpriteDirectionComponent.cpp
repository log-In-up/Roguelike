#include "pch.h"
#include "SpriteDirectionComponent.h"

namespace GameEngine
{
	SpriteDirectionComponent::SpriteDirectionComponent(GameObject* gameObject) : Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
	}

	void SpriteDirectionComponent::Render(sf::RenderWindow& window)
	{
	}

	void SpriteDirectionComponent::Update(float deltaTime)
	{
		if (input->GetHorizontalAxis() < 0)
		{
			spriteRenderer->FlipX(true);
		}
		if (input->GetHorizontalAxis() > 0)
		{
			spriteRenderer->FlipX(false);
		}
	}
}