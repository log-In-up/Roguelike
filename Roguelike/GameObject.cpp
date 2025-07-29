#include <assert.h>

#include "GameObject.h"
#include "Sprite.h"

namespace Arkanoid
{
	GameObject::GameObject(const std::string& texturePath, const sf::Vector2f& position, float width, float height) :
		startPosition(position)
	{
		sprite = new sf::Sprite();
		texture = new sf::Texture();

		assert(texture->loadFromFile(texturePath));

		InitSprite(*sprite, width, height, *texture);
		sprite->setPosition(position);
	}

	GameObject::~GameObject()
	{
		delete sprite;
		delete texture;
	}

	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(*sprite, window);
	}

	void GameObject::Restart()
	{
		sprite->setPosition(startPosition);
	}
}