#pragma once
#include <SFML/Graphics.hpp>

namespace GameEngine
{
	class RenderSystem
	{
	private:
		sf::RenderWindow* window;
	public:
		static RenderSystem* Instance();

		sf::RenderWindow& GetMainWindow() const;
		void Render(const sf::Drawable& drawable);
		void SetMainWindow(sf::RenderWindow* newWindow);

	private:
		RenderSystem() {}
		~RenderSystem() {}

		RenderSystem(RenderSystem const&) = delete;
		RenderSystem& operator= (RenderSystem const&) = delete;
	};
}