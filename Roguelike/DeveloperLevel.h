#pragma once
#include <iostream>
#include <array>

#include "Scene.h"
#include "Player.h"
#include "Music.h"
#include "Floor.h"
#include "Wall.h"

using namespace GameEngine;

namespace Roguelike
{
	class DeveloperLevel : public Scene
	{
	private:
		std::shared_ptr<Player> player;
		std::unique_ptr<Music> music;
	public:
		std::vector<std::unique_ptr<Wall>> walls;
		std::vector<std::unique_ptr<Floor>> floors;
	public:
		void Restart() override;
		void Start() override;
		void Stop() override;
	};
}