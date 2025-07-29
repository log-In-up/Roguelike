#pragma once
#include <SFML/Graphics.hpp>

#include "Collidable.h"
#include "GameObject.h"
#include "IObserver.h"

namespace Arkanoid
{
	enum class BonusType
	{
		BiggerPlatform,
		SlowBall,
		FastPlatform,

		Count
	};

	class BonusObject : public GameObject, public Colladiable, public IObservable
	{
	private:
		BonusType typeOfBonus;
	public:
		BonusType GetBonus() const
		{
			return typeOfBonus;
		}
	public:
		BonusObject(BonusType typeOfBonus, const sf::Vector2f& position);
		~BonusObject();
		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
		void Update(float timeDelta) override;
	private:
		void OnHit() override;
	};
}