#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class IDelayedAction
	{
	protected:
		bool isTimerStarted_ = false;
		float destroyTime_ = 0;
		float currentTime_ = 0;
	public:
		void StartTimer(float destroyTime)
		{
			destroyTime_ = destroyTime;
			currentTime_ = destroyTime;
			isTimerStarted_ = true;
		}
	protected:
		virtual void UpdateTimer(float deltaTime)
		{
			if (!isTimerStarted_)
			{
				return;
			}

			currentTime_ -= deltaTime;
			EachTickAction(deltaTime);

			if (currentTime_ <= 0)
			{
				FinalAction();
				isTimerStarted_ = false;
			}
		}
	protected:
		virtual void FinalAction() = 0;
		virtual void EachTickAction(float deltaTime) = 0;
	};
}