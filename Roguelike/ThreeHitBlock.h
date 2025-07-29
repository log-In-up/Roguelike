#pragma once
#include <memory>

#include "Block.h"
#include "Collidable.h"
#include "SmoothDestroyableBlock.h"

namespace Arkanoid
{
	class ThreeHitBlock : public SmoothDestroyableBlock
	{
	public:
		ThreeHitBlock(const sf::Vector2f& position);
	private:
		void OnHit() override;
		void StageChange();
	};
}
