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
	public:
		CameraComponent(GameObject* gameObject);
		~CameraComponent();

		void Render(sf::RenderWindow& window) override;
		void SetBaseResolution(int width, int height);
		void Update(float deltaTime) override;
		void ZoomBy(float newZoom);
	};
}