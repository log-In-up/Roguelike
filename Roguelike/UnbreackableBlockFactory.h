#pragma once
#include "BlockFactory.h"

namespace Arkanoid
{
	class UnbreackableBlockFactory final : public BlockFactory
	{
	public:
		~UnbreackableBlockFactory() override = default;
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
	};
}