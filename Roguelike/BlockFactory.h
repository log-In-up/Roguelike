#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace Roguelike
{
	class Block;

	class BlockFactory
	{
	protected:
		int createdBreackableBlocksCount = 0;
	public:
		virtual ~BlockFactory() = default;
		int GetcreatedBreackableBlocksCount();
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) = 0;
		void ClearCounter();
	};
}