#pragma once
#include "BlockFactory.h"

namespace Arkanoid
{
	class ThreeHitBlockFactory final : public BlockFactory
	{
	public:
		~ThreeHitBlockFactory() override = default;
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
	};
}