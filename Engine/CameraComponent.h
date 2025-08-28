#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "TransformComponent.h"

namespace GameEngine
{
	class CameraComponent : public Component
	{
	private:
		TransformComponent* transform;
		sf::View* view;
		sf::FloatRect* rectangle;
		float width;
		float height;
	public:
		CameraComponent(GameObject* gameObject, float width, float height);
		~CameraComponent();

		void Render(sf::RenderWindow& window) override;
		void Update(float deltaTime) override;
		void ZoomBy(float newZoom);
	};
}