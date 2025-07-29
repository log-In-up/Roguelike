#pragma once
#include "Ball.h"
#include "Collidable.h"
#include "GameObject.h"
#include "IDelayedAction.h"
#include "IObserver.h"

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace Arkanoid
{
	class Block : public GameObject, public Colladiable, public IObservable
	{
	protected:
		int hitCount;
		int* rewardAmount;
	public:
		Block(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		virtual ~Block();
		bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
		bool IsBroken() const;
		int GetReward() const;
		void Update(float timeDelta) override;
	protected:
		void OnHit();
	};
}