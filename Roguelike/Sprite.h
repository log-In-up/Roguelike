#pragma once
#include <list>
#include <SFML/Graphics.hpp>

#include "GameSettings.h"

namespace Arkanoid
{
	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2);

	void DrawSprite(const sf::Sprite& sprite, sf::RenderWindow& window);

	template<class InputIt>
	bool FullCheckCollisions(InputIt first, const InputIt last, const sf::Sprite& sprite) {
		for (; first != last; ++first)
		{
			if (CheckSpriteIntersection(*first, sprite))
			{
				return true;
			}
		}
		return false;
	}

	template<class InputIt>
	void DrawSprites(InputIt first, const InputIt last, sf::RenderWindow& window)
	{
		for (; first != last; ++first)
		{
			DrawSprite(*first, window);
		}
	}

	float GetManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);

	sf::Vector2f GetRandomSpritePositionInRectangle(const sf::Sprite& sprite, const sf::FloatRect& rect);

	sf::Vector2f GetVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);

	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture);

	void SetSpriteRandomPosition(sf::Sprite& sprite, const sf::FloatRect& rect, const std::list<sf::Sprite>& collection);

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
}
