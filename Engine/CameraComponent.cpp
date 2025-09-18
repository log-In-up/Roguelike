#include "pch.h"

#include "CameraComponent.h"

#include <cassert>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.h"
#include "GameObject.h"
#include "Logger.h"
#include "RenderSystem.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace GameEngine
{
CameraComponent::CameraComponent(GameObject *gameObject) : Component(gameObject)
{
    constexpr float defaultResolutionWidth = 800.0F;
    constexpr float defaultResolutionHeight = -600.0F;
    view = new sf::View(sf::FloatRect(0, 0, defaultResolutionWidth, -defaultResolutionHeight));
    transform = gameObject->GetComponent<TransformComponent>();
}

CameraComponent::~CameraComponent()
{
    delete view;
}

void CameraComponent::Update(float deltaTime)
{
    const auto &position = transform->GetWorldPosition();
    auto rotation = transform->GetWorldRotation();

    view->setCenter(Convert<sf::Vector2f>(position));
    view->setRotation(rotation);

    RenderSystem::Instance()->SetView(*view);
}

void CameraComponent::SetBaseResolution(int width, int height)
{
    view->reset(sf::FloatRect(0.0F, 0.0F, static_cast<float>(width), static_cast<float>(-height)));
}

void CameraComponent::SetWindow(sf::RenderWindow *newWindow)
{
    window = newWindow;
}

void CameraComponent::ZoomBy(float newZoom)
{
    assert(newZoom > 0.0F && "Not allowed zoom lesser or equal than zero.");
    if (newZoom <= 0)
    {
        LOG_WARN("Not allowed zoom lesser or equal than zero.");
        return;
    }
    view->zoom(newZoom);
}
} // namespace GameEngine