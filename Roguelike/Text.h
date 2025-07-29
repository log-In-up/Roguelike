#pragma once
#include <SFML/Graphics.hpp>

#include "Vector.h"

namespace Arkanoid
{
	// Helper method for organizing text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	void DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);
	void SetTextData(sf::Text& text, sf::String string, sf::Font& font, unsigned int size);
	void SetTextData(sf::Text& text, sf::String string, sf::Font& font, unsigned int size, sf::Color fillColor);
}
