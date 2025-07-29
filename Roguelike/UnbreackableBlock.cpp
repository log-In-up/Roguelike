#include "UnbreackableBlock.h"

namespace Arkanoid
{
	UnbreackableBlock::UnbreackableBlock(const sf::Vector2f& position) : Block(position, sf::Color::Color(105u, 105u, 105u))
	{
		rewardAmount = new int(0);
	}

	void UnbreackableBlock::OnHit()
	{
	}

	void UnbreackableBlock::Update(float deltaTime)
	{
	};
}