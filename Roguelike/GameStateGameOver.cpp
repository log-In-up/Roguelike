#include <assert.h>
#include <sstream>

#include "Application.h"
#include "Game.h"
#include "GameStateGameOver.h"
#include "Text.h"

namespace Arkanoid
{
	GameStateGameOverData::GameStateGameOverData()
	{
		font = new sf::Font();
		background = new sf::RectangleShape();
		gameOverText = new sf::Text();
		hintText = new sf::Text();
		recordsTableTexts = new std::vector<sf::Text>();
	}

	GameStateGameOverData::~GameStateGameOverData()
	{
		delete font;
		delete background;
		delete gameOverText;
		delete hintText;

		recordsTableTexts->clear();
		delete recordsTableTexts;
	}

	void GameStateGameOverData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background->setOrigin(0.f, 0.f);
		background->setSize(viewSize);
		window.draw(*background);

		gameOverText->setOrigin(GetTextOrigin(*gameOverText, { 0.5f, 1.f }));
		gameOverText->setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(*gameOverText);

		// We need to create new vector here as DrawItemsList needs vector of pointers
		std::vector<sf::Text*> textsList;
		textsList.reserve(recordsTableTexts->size());
		for (auto& text : *recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.f });

		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 1.f }));
		hintText->setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(*hintText);
	}

	void GameStateGameOverData::GetStateData(Memento& memento)
	{
	}

	void GameStateGameOverData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				Application::Instance().GetGame().StartGame();
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().ExitGame();
			}
		}
	}

	void GameStateGameOverData::Init()
	{
		assert(font->loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		timeSinceGameOver = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200;
		background->setFillColor(backgroundColor);

		SetTextData(*gameOverText, "GAME OVER", *font, 48, sf::Color::Red);
		gameOverText->setStyle(sf::Text::Bold);

		recordsTableTexts->reserve(SETTINGS.MAX_RECORDS_TABLE_SIZE);

		std::multimap<int, std::string> sortedRecordsTable;
		Game& game = Application::Instance().GetGame();
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isPlayerInTable = false;
		auto it = sortedRecordsTable.rbegin();

		for (int i = 0; i < SETTINGS.MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) // Note, we can do several actions in for action block
		{
			recordsTableTexts->emplace_back(); // Create text in place
			sf::Text& text = recordsTableTexts->back();

			// We can use streams for writing into string and reading from it
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			SetTextData(text, sstream.str(), *font, 24);

			if (it->second == SETTINGS.PLAYER_NAME)
			{
				text.setFillColor(sf::Color::Green);
				isPlayerInTable = true;
			}
			else
			{
				text.setFillColor(sf::Color::White);
			}
		}

		if (!isPlayerInTable)
		{
			sf::Text& text = recordsTableTexts->back();
			std::stringstream sstream;

			int playerScores = game.GetRecordByPlayerId(SETTINGS.PLAYER_NAME);
			sstream << SETTINGS.MAX_RECORDS_TABLE_SIZE << ". " << SETTINGS.PLAYER_NAME << ": " << playerScores;

			text.setString(sstream.str());
			text.setFillColor(sf::Color::Green);
		}

		SetTextData(*hintText, "Press Space to restart\nEsc to exit to main menu", *font, 24, sf::Color::White);
	}

	void GameStateGameOverData::SetStateData(Memento& memento)
	{
	}

	void GameStateGameOverData::Update(float timeDelta)
	{
		timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		gameOverText->setFillColor(gameOverTextColor);
	}
}