#pragma once
#include "GameObject.h"
#include "PhysicsSystem.h"

namespace GameEngine
{
	class GameWorld
	{
	private:
		std::vector<GameObject*> gameObjects = {};
		std::vector<GameObject*> markedToDestroyGameObjects = {};

		float fixedCounter = 0.f;
	public:
		static GameWorld* Instance();

		GameObject* CreateGameObject();
		GameObject* CreateGameObject(std::string name);
		void Clear();
		void DestroyGameObject(GameObject* gameObject);
		void FixedUpdate(float deltaTime);
		void LateUpdate();
		void Print() const;
		void Render(sf::RenderWindow& window);
		void Update(float deltaTime);
	private:
		GameWorld() {}
		~GameWorld() {}

		GameWorld(GameWorld const&) = delete;
		GameWorld& operator= (GameWorld const&) = delete;

		void DestroyGameObjectImmediate(GameObject* gameObject);
	};
}