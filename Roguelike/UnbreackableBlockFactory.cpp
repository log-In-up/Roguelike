#include "UnbreackableBlock.h"
#include "UnbreackableBlockFactory.h"

namespace Arkanoid
{
	std::shared_ptr<Block> UnbreackableBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		return std::make_shared<UnbreackableBlock>(position);
	}
}