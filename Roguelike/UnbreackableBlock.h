#pragma once
#include "Block.h"

namespace Arkanoid
{
	class UnbreackableBlock : public Block
	{
	public:
		UnbreackableBlock(const sf::Vector2f& position);
		void OnHit() override;
		void Update(float deltaTime);
	};
}
