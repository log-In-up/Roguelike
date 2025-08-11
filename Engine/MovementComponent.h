#pragma once
#include "GameObject.h"
#include "InputComponent.h"

namespace GameEngine
{
	class MovementComponent : public Component
	{
	private:
		InputComponent* input;
		TransformComponent* transform;

		float speed = 0;
		Vector2Df previousPosition = { 0, 0 };
		Vector2Df acceleration = { 0, 0 };
	public:
		MovementComponent(GameObject* gameObject);

		float GetAccelerationSquared() const;
		float GetSpeed() const;
		void Render(sf::RenderWindow& window) override;
		void SetSpeed(float newSpeed);
		void Update(float deltaTime) override;
	};
}