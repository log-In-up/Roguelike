#include "BonusObject.h"
#include "GameSettings.h"
#include "Platform.h"
#include <cassert>

namespace
{
	const std::string TEXTURE_ID = "ball";
}

namespace Arkanoid
{
	BonusObject::BonusObject(BonusType typeOfBonus, const sf::Vector2f& position)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, (float)SETTINGS.BONUS_BALL_SIZE, (float)SETTINGS.BONUS_BALL_SIZE)
	{
		this->typeOfBonus = typeOfBonus;
	}

	BonusObject::~BonusObject()
	{
	}

	bool BonusObject::GetCollision(std::shared_ptr<Colladiable> collidable) const
	{
		auto platform = std::static_pointer_cast<Platform>(collidable);
		assert(platform);

		return GetRect().intersects(platform->GetRect());
	}

	void BonusObject::Update(float timeDelta)
	{
		sf::Vector2f position = sprite->getPosition();
		position.y -= timeDelta * -SETTINGS.BONUS_BALL_SPEED;

		sprite->setPosition(position);
	}

	void BonusObject::OnHit()
	{
		Emit();
	}
}