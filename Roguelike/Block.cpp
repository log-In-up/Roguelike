#include <assert.h>

#include "Block.h"
#include "GameSettings.h"
#include "Sprite.h"

namespace Arkanoid
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, (float)SETTINGS.BLOCK_WIDTH, (float)SETTINGS.BLOCK_HEIGHT)
	{
		hitCount = 1;
		sprite->setColor(color);
		rewardAmount = new int(const_cast<unsigned int&>(SETTINGS.BLOCK_REWARD));
	}

	Block::~Block()
	{
		delete rewardAmount;
	}

	bool Block::GetCollision(std::shared_ptr<Colladiable> collidableObject) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);

		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;

		return GetRect().intersects(gameObject->GetRect());
	}

	bool Block::IsBroken() const
	{
		return hitCount <= 0;
	}

	int Block::GetReward() const
	{
		return *rewardAmount;
	}

	void Block::Update(float timeDelta)
	{
	}

	void Block::OnHit()
	{
		hitCount = 0;
		Emit();
	}
}