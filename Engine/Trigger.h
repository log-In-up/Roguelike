#pragma once
namespace GameEngine
{
	class ColliderComponent;

	struct Trigger
	{
	private:
		ColliderComponent* first;
		ColliderComponent* second;
	public:
		ColliderComponent& GetFirstComponent()
		{
			return *first;
		}

		ColliderComponent& GetSecondComponent()
		{
			return *second;
		}
	public:
		Trigger(ColliderComponent* newFirst, ColliderComponent* newSecond) : first(newFirst), second(newSecond)
		{
		};
	};
}