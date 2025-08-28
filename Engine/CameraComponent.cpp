#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"

namespace GameEngine
{
	CameraComponent::CameraComponent(GameObject* gameObject, float width, float height) : Component(gameObject)
	{
		this->width = width;
		this->height = height;

		rectangle = new sf::FloatRect(0, 0, width, height);
		view = new sf::View(*rectangle);

		transform = gameObject->GetComponent<TransformComponent>();
	}

	CameraComponent::~CameraComponent()
	{
		view->setRotation(0.f);
		view->setCenter(sf::Vector2f(width / 2, height / 2));
		RenderSystem::Instance()->GetMainWindow().setView(*view);

		delete view;
		delete rectangle;
	}

	void CameraComponent::Update(float deltaTime)
	{
		auto position = transform->GetWorldPosition();
		auto rotation = transform->GetWorldRotation() + 180.f;

		if (rotation >= 360.f)
		{
			rotation -= 360.f;
		}

		view->setCenter(Convert<sf::Vector2f, Vector2Df>(position));
		view->setRotation(rotation);
	}

	void CameraComponent::Render(sf::RenderWindow& window)
	{
		window.setView(*view);
	}

	void CameraComponent::ZoomBy(float newZoom)
	{
		if (newZoom <= 0)
		{
			std::cout << "Not allowed zoom lesser or equal than zero." << std::endl;
			return;
		}
		view->zoom(newZoom);
	}
}