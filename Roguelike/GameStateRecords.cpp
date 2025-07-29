#include <assert.h>
#include <sstream>

#include "Application.h"
#include "Game.h"
#include "GameSettings.h"
#include "GameStateRecords.h"
#include "Text.h"

namespace Arkanoid
{
	GameStateRecordsData::GameStateRecordsData()
	{
		font = new sf::Font();
		hintText = new sf::Text();
		titleText = new sf::Text();
		tableTexts = new std::vector<sf::Text>();
	}

	GameStateRecordsData::~GameStateRecordsData()
	{
		delete font;
		delete hintText;
		delete titleText;

		tableTexts->clear();
		delete tableTexts;
	}

	void GameStateRecordsData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		titleText->setOrigin(GetTextOrigin(*titleText, { 0.5f, 0.f }));
		titleText->setPosition(viewSize.x / 2.f, 50.f);
		window.draw(*titleText);

		std::vector<sf::Text*> textsList;
		textsList.reserve(tableTexts->size());

		for (auto& text : *tableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { titleText->getGlobalBounds().left, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.f, 0.f });

		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 1.f }));
		hintText->setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(*hintText);
	}

	void GameStateRecordsData::GetStateData(Memento& memento)
	{
	}

	void GameStateRecordsData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}
		}
	}

	void GameStateRecordsData::Init()
	{
		assert(font->loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		SetTextData(*titleText, "RECORDS", *font, 48, sf::Color::Red);

		tableTexts->reserve(SETTINGS.MAX_RECORDS_TABLE_SIZE);

		const Game& game = Application::Instance().GetGame();
		std::map<int, std::string> sortedRecordsTable;
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable[item.second] = item.first;
		}

		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < SETTINGS.MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) // Note, we can do several actions in for action block
		{
			tableTexts->emplace_back(); // Create text in place
			sf::Text& text = tableTexts->back();

			// We can use streams for writing into string and reading from it
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;

			SetTextData(text, sstream.str(), *font, 24, sf::Color::White);
		}

		SetTextData(*hintText, "Press ESC to return back to main menu", *font, 24, sf::Color::White);
	}

	void GameStateRecordsData::SetStateData(Memento& memento)
	{
	}

	void GameStateRecordsData::Update(float timeDelta)
	{
	}
}