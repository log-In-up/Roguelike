#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

#include "TransformComponent.h"
#include "Vector.h"

namespace GameEngine
{
	class SpriteRendererComponent : public Component
	{
	private:
		Vector2Df scale;
		sf::Sprite* sprite;
		TransformComponent* transform;

		bool isFlipX = false;
		bool isFlipY = false;
	public:
		SpriteRendererComponent(GameObject* gameObject);
		~SpriteRendererComponent();

		const sf::Sprite* GetSprite() const;
		void FlipX(bool flip);
		void FlipY(bool flip);
		void Render(sf::RenderWindow& window) override;
		void SetPixelSize(int newWidth, int newHeight);
		void SetTexture(const sf::Texture& newTexture);
		void Update(float deltaTime) override;
	};
}