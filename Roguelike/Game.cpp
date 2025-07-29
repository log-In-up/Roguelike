#include <algorithm>
#include <assert.h>

#include "Game.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStatePauseMenu.h"
#include "GameStatePlaying.h"
#include "GameStateRecords.h"

namespace Arkanoid
{
	Game::Game()
	{
		stateStack = new std::vector<GameState>();
		caretaker = new Caretaker(*stateStack);

		recordsTable = new RecordsTable();
		recordsTable->insert({ "John", SETTINGS.MAX_APPLES / 2 });
		recordsTable->insert({ "Jane", SETTINGS.MAX_APPLES / 3 });
		recordsTable->insert({ "Alice", SETTINGS.MAX_APPLES / 4 });
		recordsTable->insert({ "Bob", SETTINGS.MAX_APPLES / 5 });
		recordsTable->insert({ "Clementine", SETTINGS.MAX_APPLES / 5 });
		recordsTable->insert({ SETTINGS.PLAYER_NAME, 0 });

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		stateStack->clear();
		delete stateStack;

		delete caretaker;

		recordsTable->clear();
		delete recordsTable;

		Shutdown();
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable->find(playerId);
		return it == recordsTable->end() ? 0 : it->second;
	}

	void Game::ExitGame()
	{
		SwitchStateTo(GameStateType::MainMenu);
	}

	void Game::LoadNextLevel()
	{
		assert(stateStack->back().GetType() == GameStateType::Playing);
		auto playingData = (stateStack->back().GetData<GameStatePlayingData>());
		playingData->LoadNextLevel();

		caretaker->Save();
	}

	void Game::LooseGame()
	{
		PushState(GameStateType::GameOver, false);
	}

	void Game::PauseGame()
	{
		PushState(GameStateType::ExitDialog, false);
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::QuitGame()
	{
		SwitchStateTo(GameStateType::None);
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value)
		{
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else
		{
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	void Game::ShowRecords()
	{
		PushState(GameStateType::Records, true);
	}

	void Game::StartGame()
	{
		recordsTable->at(SETTINGS.PLAYER_NAME) = 0;

		SwitchStateTo(GameStateType::Playing);
	}

	void Game::UpdateGame(float timeDelta, sf::RenderWindow& window)
	{
		HandleWindowEvents(window);

		if (Update(timeDelta))
		{
			window.clear();
			Draw(window);
			window.display();
		}
		else
		{
			window.close();
		}
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable->at(playerId) = std::max(recordsTable->at(playerId), score);
	}

	void Game::WinGame()
	{
		PushState(GameStateType::GameWin, false);
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			while (stateStack->size() > 0)
			{
				stateStack->pop_back();
			}
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			if (stateStack->size() > 0)
			{
				stateStack->pop_back();
			}
		}

		if (pendingGameStateType != GameStateType::None)
		{
			stateStack->push_back(GameState(pendingGameStateType, pendingGameStateIsExclusivelyVisible));

			caretaker->Undo();
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack->size() > 0)
		{
			stateStack->back().Update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack->size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack->rbegin(); it != stateStack->rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->IsExclusivelyVisible())
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->Draw(window);
			}
		}
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack->size() > 0)
			{
				stateStack->back().HandleWindowEvent(event);
			}
		}
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;

		caretaker->Save();
	}

	void Game::Shutdown()
	{
		while (stateStack->size() > 0)
		{
			stateStack->pop_back();
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;

		caretaker->Save();
	}
}