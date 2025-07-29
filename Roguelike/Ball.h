#pragma once
#include <SFML/Graphics.hpp>

#include "Collidable.h"
#include "GameObject.h"
#include "IObserver.h"

namespace Arkanoid
{
	class Ball final : public GameObject, public Colladiable, public IObservable
	{
	private:
		sf::Vector2f* direction;
		float* lastAngle;
		float* multiplySpeed;
	public:
		Ball(const sf::Vector2f& position);
		~Ball();
		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
		void Restart() override;
		void Update(float timeDelta) override;

		void ChangeAngle(float x);
		void ChangeSpeed(float multipleSpeed);
		void InvertDirectionX();
		void InvertDirectionY();
	private:
		void OnHit();
	};
}
