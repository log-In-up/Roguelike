#include "SimpleBlockFactory.h"
#include "SmoothDestroyableBlock.h"

namespace Roguelike
{
	std::shared_ptr<Block> SimpleBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		++createdBreackableBlocksCount;
		return std::make_shared<SmoothDestroyableBlock>(position);
	}
}