#pragma once
#include <SFML/Graphics.hpp>

#include "Game.h"

namespace Arkanoid
{
	class Application
	{
	private:
		Game* game;
		sf::RenderWindow* window;
	public:
		Game& GetGame()
		{
			return *game;
		}
	public:
		Application(const Application& app) = delete;

		Application& operator= (const Application&) = delete;

		static Application& Instance();
		void Run();
	private:
		Application();
		~Application();
	};
}
