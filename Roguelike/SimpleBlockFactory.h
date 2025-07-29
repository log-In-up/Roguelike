#pragma once
#include "BlockFactory.h"

namespace Arkanoid
{
	class SimpleBlockFactory final : public BlockFactory
	{
	public:
		~SimpleBlockFactory() override = default;
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
	};
}