#pragma once
#include "GameObject.h"
#include "MovementComponent.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"

namespace GameEngine
{
	class SpriteMovementAnimationComponent : public Component
	{
	private:
		MovementComponent* movement;
		SpriteRendererComponent* renderer;

		std::vector<const sf::Texture*> textureMap;
		float secondsForFrame = 0.f;

		float counter = 0.f;
		int frame = 0;
	public:
		SpriteMovementAnimationComponent(GameObject* gameObject);

		void Initialize(const std::string& textureMapName, float newFramerate);
		void Render(sf::RenderWindow& window) override;
		void Update(float deltaTime) override;
	};
}
