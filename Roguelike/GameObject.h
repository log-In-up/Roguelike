#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class GameObject
	{
	protected:
		sf::Sprite* sprite;
		sf::Texture* texture;
		const sf::Vector2f startPosition;
	public:
		const sf::Vector2f& GetPosition() const
		{
			return sprite->getPosition();
		}

		sf::FloatRect GetRect() const
		{
			return sprite->getGlobalBounds();
		}
	public:
		GameObject(const std::string& textureId, const sf::Vector2f& position, float width, float height);
		virtual ~GameObject();

		virtual void Draw(sf::RenderWindow& window);
		virtual void Restart();
		virtual void Update(float timeDelta) = 0;
	};
}