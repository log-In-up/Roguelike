#include <SFML/Graphics.hpp>
#include <RenderSystem.h>

#include "Application.h"
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"

using namespace Roguelike;

int main()
{
	//RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(
	//	sf::VideoMode(Roguelike::SETTINGS.SCREEN_WIDTH, Roguelike::SETTINGS.SCREEN_HEIGHT), Roguelike::SETTINGS.GAME_NAME));

	////XYZEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");

	//ResourceSystem::Instance()->LoadTextureMap("player", "Resources/TextureMaps/Player.png", { 48, 63 }, 4, false);
	//ResourceSystem::Instance()->LoadTextureMap("level_floors", "Resources/TextureMaps/Floor.png", { 16, 16 }, 49, false);
	//ResourceSystem::Instance()->LoadTextureMap("level_walls", "Resources/TextureMaps/Wall.png", { 16, 16 }, 48, false);

	//ResourceSystem::Instance()->LoadSound("music", "Resources/Sounds/AppleEat.wav");

	//auto developerLevel = std::make_shared<DeveloperLevel>();
	//developerLevel->Start();

	//GameEngine::Engine::Instance()->Run();

	Roguelike::Application::Instance().Run();

	return 0;
}