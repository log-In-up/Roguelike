#include "pch.h"
#include "MovementComponent.h"
namespace GameEngine
{
	MovementComponent::MovementComponent(GameObject* gameObject) : Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		transform = gameObject->GetComponent<TransformComponent>();

		if (input == nullptr)
		{
			std::cout << "Need input component for movement" << std::endl;
			gameObject->RemoveComponent(this);
		}
	}

	float MovementComponent::GetAccelerationSquared() const
	{
		return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
	}

	float MovementComponent::GetSpeed() const
	{
		return speed;
	}

	void MovementComponent::Render(sf::RenderWindow& window)
	{
	}

	void MovementComponent::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	void MovementComponent::Update(float deltaTime)
	{
		float xAxis = input->GetHorizontalAxis();
		float yAxis = input->GetVerticalAxis();

		transform->MoveBy(speed * deltaTime * Vector2Df{ xAxis, yAxis });

		acceleration = transform->GetWorldPosition() - previousPosition;
		previousPosition = transform->GetWorldPosition();
	}
}