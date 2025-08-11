#include "pch.h"
#include "RigidbodyComponent.h"

namespace GameEngine
{
	RigidbodyComponent::RigidbodyComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
	}

	bool RigidbodyComponent::GetKinematic() const
	{
		return isKinematic;
	}

	float RigidbodyComponent::GetAngleDamping() const
	{
		return angleDamping;
	}

	float RigidbodyComponent::GetAngleVelocity() const
	{
		return angleVelocity;
	}

	float RigidbodyComponent::GetLinearDamping() const
	{
		return linearDamping;
	}

	Vector2Df RigidbodyComponent::GetLinearVelocity() const
	{
		return linearVelocity;
	}

	void RigidbodyComponent::AddAngleVelocity(float angleOffset)
	{
		angleVelocity += angleOffset;
	}

	void RigidbodyComponent::AddLinearVelocity(Vector2Df linearOffset)
	{
		linearVelocity = linearVelocity + linearOffset;
	}

	void RigidbodyComponent::Render(sf::RenderWindow& window)
	{
	}

	void RigidbodyComponent::SetAngleDamping(float newAngleDamping)
	{
		angleDamping = newAngleDamping;
	}

	void RigidbodyComponent::SetAngleVelocity(float newAngleVelocity)
	{
		angleVelocity = newAngleVelocity;
	}

	void RigidbodyComponent::SetKinematic(bool newIsKinematic)
	{
		isKinematic = newIsKinematic;
	}

	void RigidbodyComponent::SetLinearDamping(float newLinearDamping)
	{
		linearDamping = newLinearDamping;
	}

	void RigidbodyComponent::SetLinearVelocity(Vector2Df newLinearVelocity)
	{
		linearVelocity = newLinearVelocity;
	}

	void RigidbodyComponent::Update(float deltaTime)
	{
		transform->MoveBy(linearVelocity);
		transform->RotateBy(angleVelocity);

		linearVelocity = (1.f - linearDamping * deltaTime) * linearVelocity;
		angleVelocity = (1.f - angleDamping * deltaTime) * angleVelocity;

		if (linearVelocity.x < 0.001f)
		{
			linearVelocity = { 0.f, linearVelocity.y };
		}
		if (linearVelocity.y < 0.001f)
		{
			linearVelocity = { linearVelocity.x, 0.f };
		}

		if (angleVelocity < 0.001f)
		{
			angleVelocity = 0.f;
		}
	}
}