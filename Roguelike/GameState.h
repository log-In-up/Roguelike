#pragma once
#include <SFML/Graphics.hpp>

#include "GameStateData.h"
#include "Memento.h"

namespace Arkanoid
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		GameWin,
		ExitDialog,
		Records,
	};

	class GameState
	{
	private:
		std::shared_ptr<GameStateData> data = nullptr;
		GameStateType type = GameStateType::None;
		bool isExclusivelyVisible = false;
	public:
		GameState(GameState&& state) noexcept
		{
			operator=(std::move(state));
		}

		bool IsExclusivelyVisible() const
		{
			return isExclusivelyVisible;
		}

		GameStateType GetType() const
		{
			return type;
		}

		template<class T>
		T* GetData() const
		{
			return static_cast<T*>(data.get());
		}

		GameState& operator= (GameState&& state) noexcept
		{
			type = state.type;
			data = std::move(state.data);
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;
			return *this;
		}

	public:
		GameState() = default;
		GameState(const GameState& state) = delete;
		GameState(GameStateType type, bool isExclusivelyVisible);
		~GameState();

		GameState& operator= (const GameState& state) = delete;

		void Draw(sf::RenderWindow& window);
		void GetGameStateData(Memento& memento);
		void HandleWindowEvent(sf::Event& event);
		void SetGameStateData(Memento& memento);
		void Update(float timeDelta);
	};
}