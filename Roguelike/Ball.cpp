#include <assert.h>

#include "Ball.h"
#include "GameSettings.h"
#include "randomizer.h"
#include "Sprite.h"

namespace
{
	const std::string TEXTURE_ID = "ball";
}

namespace Arkanoid
{
	Ball::Ball(const sf::Vector2f& position)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, (float)SETTINGS.BALL_SIZE, (float)SETTINGS.BALL_SIZE)
	{
		const float angle = 90;
		const float pi = std::acos(-1.f);

		direction = new sf::Vector2f(std::cos(pi / 180.f * angle), std::sin(pi / 180.f * angle));

		lastAngle = new float(90.f);
		multiplySpeed = new float(1.f);
	}

	Ball::~Ball()
	{
		delete direction;
		delete lastAngle;
		delete multiplySpeed;
	}

	bool Ball::GetCollision(std::shared_ptr<Colladiable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);

		return GetRect().intersects(gameObject->GetRect());
	}

	void Ball::Restart()
	{
		GameObject::Restart();

		const float angle = 90;
		const float pi = std::acos(-1.f);

		direction->x = std::cos(pi / 180.f * angle);
		direction->y = std::sin(pi / 180.f * angle);
	}

	void Ball::Update(float timeDelta)
	{
		timeDelta = *multiplySpeed * timeDelta;
		const sf::Vector2f position = sprite->getPosition() + SETTINGS.BALL_SPEED * timeDelta * *direction;
		sprite->setPosition(position);

		if (position.x - SETTINGS.BALL_SIZE / 2.f <= 0 || position.x + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_WIDTH)
		{
			direction->x *= -1;
		}

		if (position.y - SETTINGS.BALL_SIZE / 2.f <= 0 || position.y + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_HEIGHT)
		{
			direction->y *= -1;
		}
		Emit();
	}

	void Ball::ChangeAngle(float angle)
	{
		*lastAngle = angle;

		const float pi = std::acos(-1.f);
		direction->x = (angle / abs(angle)) * std::cos(pi / 180.f * angle);
		direction->y = -1 * abs(std::sin(pi / 180.f * angle));
	}

	void Ball::ChangeSpeed(float multipleSpeed)
	{
		*multiplySpeed = multipleSpeed;
	}

	void Ball::InvertDirectionX()
	{
		direction->x *= -1;
	}

	void Ball::InvertDirectionY()
	{
		direction->y *= -1;
	}

	void Ball::OnHit()
	{
		*lastAngle += random<float>(-5, 5);
		ChangeAngle(*lastAngle);
	}
}