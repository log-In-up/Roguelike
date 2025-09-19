#include "pch.h"

#include "Component.h"

#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>

#include "Logger.h"

namespace GameEngine
{
Component::Component(GameObject *gameObject) : gameObject(gameObject)
{
    assert(gameObject != nullptr && "GameObject pointer must not be null");
    if (gameObject == nullptr)
    {
        LOG_WARN("Component with nullptr GameOnject constructed");
    }
}

Component::~Component()
{
    try
    {
        std::ostringstream message;
        message << "Deleted component: " << typeid(this).name() << " " << this << std::endl;
        LOG_INFO(message.str());
    }
    catch (const std::exception &exception)
    {
        std::cerr << "Logging failed: " << exception.what() << std::endl;
    }
}

GameObject *Component::GetGameObject()
{
    return gameObject;
}
} // namespace GameEngine