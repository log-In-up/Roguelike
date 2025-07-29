#include <assert.h>

#include "GameSettings.h"
#include "SmoothDestroyableBlock.h"

namespace Arkanoid
{
	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color) : Block(position, color)
	{
		this->color = new sf::Color(color);
	}

	SmoothDestroyableBlock::~SmoothDestroyableBlock()
	{
		delete color;
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<Colladiable> collidableObject) const
	{
		if (isTimerStarted_)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);

		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;

		return GetRect().intersects(gameObject->GetRect());
	}

	void SmoothDestroyableBlock::EachTickAction(float deltaTime)
	{
		color->a = (sf::Uint8)(255 * currentTime_ / destroyTime_);
		sprite->setColor(*color);
	}

	void SmoothDestroyableBlock::FinalAction()
	{
		--hitCount;
		Emit();
	}

	void SmoothDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	void SmoothDestroyableBlock::OnHit()
	{
		StartTimer(SETTINGS.BREAK_DELAY);
	}
}