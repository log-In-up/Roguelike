#pragma once
#include "TransformComponent.h"
#include "Vector.h"

namespace GameEngine
{
	class RigidbodyComponent : public Component
	{
	private:
		TransformComponent* transform;

		Vector2Df linearVelocity = { 0.f, 0.f };
		float angleVelocity = 0.f;

		float linearDamping = 0.f;
		float angleDamping = 0.f;

		bool isKinematic = false;
	public:
		RigidbodyComponent(GameObject* gameObject);

		bool GetKinematic() const;
		float GetAngleDamping() const;
		float GetAngleVelocity() const;
		float GetLinearDamping() const;
		Vector2Df GetLinearVelocity() const;
		void AddAngleVelocity(float angleOffset);
		void AddLinearVelocity(Vector2Df linearOffset);
		void Render(sf::RenderWindow& window) override;
		void SetAngleDamping(float newAngleDamping);
		void SetAngleVelocity(float newAngleVelocity);
		void SetKinematic(bool newIsKinematic);
		void SetLinearDamping(float newLinearDamping);
		void SetLinearVelocity(Vector2Df newLinearVelocity);
		void Update(float deltaTime) override;
	};
}