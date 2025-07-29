#pragma once
#include "Block.h"
#include "IDelayedAction.h"

namespace Arkanoid
{
	class SmoothDestroyableBlock : public Block, public IDelayedAction
	{
	protected:
		sf::Color* color;
	public:
		SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		~SmoothDestroyableBlock();

		bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
		void EachTickAction(float deltaTime) override;
		void FinalAction() override;
		void Update(float timeDelta) override;
	protected:
		void OnHit() override;
	};
}