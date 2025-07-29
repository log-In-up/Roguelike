#include <algorithm>

#include "Ball.h"
#include "GameSettings.h"
#include "Platform.h"
#include "Sprite.h"
#include "BonusObject.h"

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace Arkanoid
{
	Platform::Platform(const sf::Vector2f& position)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, (float)SETTINGS.PLATFORM_WIDTH, (float)SETTINGS.PLATFORM_HEIGHT)
	{
		speed = SETTINGS.PLATFORM_SPEED;
	}

	bool Platform::CheckCollision(std::shared_ptr<Colladiable> collidable)
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball)
		{
			return false;
		}

		if (GetCollision(ball))
		{
			auto rect = GetRect();
			auto ballPosInOlatform = (ball->GetPosition().x - (rect.left + rect.width / 2)) / (rect.width / 2);
			ball->ChangeAngle(90 - 20 * ballPosInOlatform);

			return true;
		}
		return false;
	}

	bool Platform::GetCollision(std::shared_ptr<Colladiable> collidable) const
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball)
		{
			return false;
		}

		auto sqr = [](float x) { return x * x; };

		const auto rect = sprite->getGlobalBounds();
		const auto ballPos = ball->GetPosition();

		if (ballPos.x < rect.left)
		{
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.f);
		}

		if (ballPos.x > rect.left + rect.width)
		{
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.f);
		}

		return std::fabs(ballPos.y - rect.top) <= SETTINGS.BALL_SIZE / 2.0;
	}

	void Platform::ChangeSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	void Platform::ChangeWidth(float multiplyWidth)
	{
		sprite->scale(sf::Vector2f(multiplyWidth, 1));
	}

	void Platform::OnHit()
	{
	}

	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Move(-timeDelta * speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Move(timeDelta * speed);
		}
	}

	void Platform::Move(float speed)
	{
		auto position = sprite->getPosition();
		position.x = std::clamp(position.x + speed, SETTINGS.PLATFORM_WIDTH / 2.f, SETTINGS.SCREEN_WIDTH - SETTINGS.PLATFORM_WIDTH / 2.f);
		sprite->setPosition(position);
	}
}