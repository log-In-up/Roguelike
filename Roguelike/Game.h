#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "GameSettings.h"
#include "GameState.h"
#include "Sprite.h"

namespace Roguelike
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
		bool Update(float timeDelta); /// Return false if game should be closed
		int GetRecordByPlayerId(const std::string& playerId) const;
		void Draw(sf::RenderWindow& window);
		void ExitGame();
		void HandleWindowEvents(sf::RenderWindow& window);
		void LoadNextLevel();
		void LooseGame();
		void PauseGame();
		void PopState(); /// Remove current game state from the stack
		void QuitGame();
		void SetOption(GameOptions option, bool value);
		void ShowRecords();
		void StartGame();
		void UpdateGame(float timeDelta, sf::RenderWindow& window);
		void UpdateRecord(const std::string& playerId, int score);
		void WinGame();
	private:
		/// Add new game state on top of the stack
		void PushState(GameStateType stateType, bool isExclusivelyVisible);
		void Shutdown();
		/// Remove all game states from the stack and add new one
		void SwitchStateTo(GameStateType newState);
	};
}
