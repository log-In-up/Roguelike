#include <iostream>

#include "pch.h"
#include "Component.h"

namespace GameEngine
{
	Component::Component(GameObject* gameObject) : gameObject(gameObject)
	{
	}

	Component::~Component()
	{
		std::cout << "Deleted component: " << this << std::endl;
	}

	GameObject* Component::GetGameObject()
	{
		return gameObject;
	}
}