#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "ColliderComponent.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

namespace GameEngine
{
	class SpriteColliderComponent : public ColliderComponent
	{
	private:
		const sf::Sprite* sprite;
	public:
		SpriteColliderComponent(GameObject* gameObject);
		~SpriteColliderComponent();

		void Render(sf::RenderWindow& window) override;
		void Update(float deltaTime) override;
	};
}
