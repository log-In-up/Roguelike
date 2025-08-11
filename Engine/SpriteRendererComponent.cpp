#include "pch.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"

namespace GameEngine
{
	SpriteRendererComponent::SpriteRendererComponent(GameObject* gameObject) : Component(gameObject)
	{
		sprite = new sf::Sprite();
		scale = { 1, -1 };
		sprite->setScale({ 1, -1 });
		transform = gameObject->GetComponent<TransformComponent>();
	}

	SpriteRendererComponent::~SpriteRendererComponent()
	{
		if (sprite != nullptr)
		{
			delete sprite;
		}
	}

	const sf::Sprite* SpriteRendererComponent::GetSprite() const
	{
		return sprite;
	}

	void SpriteRendererComponent::FlipX(bool flip)
	{
		if (flip != isFlipX)
		{
			scale = { -scale.x, scale.y };
			isFlipX = flip;
		}
	}

	void SpriteRendererComponent::FlipY(bool flip)
	{
		if (flip != isFlipY)
		{
			scale = { scale.x, -scale.y };
			isFlipY = flip;
		}
	}

	void SpriteRendererComponent::Render(sf::RenderWindow& window)
	{
		if (sprite != nullptr)
		{
			sprite->setPosition(Convert<sf::Vector2f, Vector2Df>(transform->GetWorldPosition()));
			sprite->setRotation(transform->GetWorldRotation());

			auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
			sprite->setScale({ scale.x * transformScale.x, scale.y * transformScale.y });
			RenderSystem::Instance()->Render(*sprite);
		}
	}

	void SpriteRendererComponent::SetPixelSize(int newWidth, int newHeight)
	{
		auto originalSize = sprite->getTexture()->getSize();
		scale = { (float)newWidth / (float)originalSize.x, -(float)newHeight / (float)originalSize.y };
	}

	void SpriteRendererComponent::SetTexture(const sf::Texture& newTexture)
	{
		sprite->setTexture(newTexture);
		auto textureSize = sprite->getTexture()->getSize();
		sprite->setOrigin({ 0.5f * textureSize.x, 0.5f * textureSize.y });
	}

	void SpriteRendererComponent::Update(float deltaTime)
	{
	}
}