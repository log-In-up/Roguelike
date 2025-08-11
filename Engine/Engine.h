#pragma once
#define NOMINMAX

#include <SFML/Graphics.hpp>

namespace GameEngine
{
	class Engine
	{
	public:
		Engine(const Engine& app) = delete;
		Engine& operator= (const Engine&) = delete;

		static Engine* Instance();

		void Run();

	private:
		Engine();
		~Engine() = default;

		void setupLogger();
	};
}