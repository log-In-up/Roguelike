#include "ThreeHitBlock.h"
#include "ThreeHitBlockFactory.h"

namespace Arkanoid
{
	std::shared_ptr<Block> ThreeHitBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		++createdBreackableBlocksCount;
		return std::make_shared<ThreeHitBlock>(position);
	}
}