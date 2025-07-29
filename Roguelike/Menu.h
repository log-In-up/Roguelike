#pragma once
#include <functional>
#include <list>
#include <SFML/Graphics.hpp>

#include "Text.h"

namespace Arkanoid
{
	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText; // Visible when child item is selected
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;

		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;

		std::vector<MenuItem> childrens;

		std::function<void(MenuItem& item)> onPressCallback;

		MenuItem* parent = nullptr;

		float childrenSpacing = 10.f;
		bool isEnabled = true;
	};

	class Menu
	{
	private:
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;
	public:
		MenuItem& GetCurrentContext();
		void Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
		void GoBack();	// go back to previous menu
		void Init(const MenuItem& item);
		void PressOnSelectedItem();	// press on selected menu item
		void SwitchToNextMenuItem();
		void SwitchToPreviousMenuItem();
		void Update(float deltaTime);
	private:
		void InitMenuItem(MenuItem& item);
		void SelectMenuItem(MenuItem& item);
	};
}
