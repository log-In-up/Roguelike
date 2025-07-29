#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "GameSettings.h"
#include "GameState.h"
#include "Sprite.h"
#include "Caretaker.h"

namespace Arkanoid
{
	enum class GameOptions : std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	private:
		using RecordsTable = std::unordered_map<std::string, int>;

		std::vector<GameState>* stateStack;

		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;

		RecordsTable* recordsTable;
		Caretaker* caretaker;

		GameOptions options = GameOptions::Default;
		bool pendingGameStateIsExclusivelyVisible = false;
	public:
		const RecordsTable& GetRecordsTable() const
		{
			return *recordsTable;
		}
	public:
		Game();
		~Game();
		bool IsEnableOptions(GameOptions option) const;
		int GetRecordByPlayerId(const std::string& playerId) const;
		void ExitGame();
		void LoadNextLevel();
		void LooseGame();
		void PauseGame();
		/// Remove current game state from the stack
		void PopState();
		void QuitGame();
		void SetOption(GameOptions option, bool value);
		void ShowRecords();
		void StartGame();
		void UpdateGame(float timeDelta, sf::RenderWindow& window);
		void UpdateRecord(const std::string& playerId, int score);
		void WinGame();
	private:
		/// Return false if game should be closed
		bool Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvents(sf::RenderWindow& window);
		/// Add new game state on top of the stack
		void PushState(GameStateType stateType, bool isExclusivelyVisible);
		void Shutdown();
		/// Remove all game states from the stack and add new one
		void SwitchStateTo(GameStateType newState);
	};
}
