#include "menu.h"



menu::menu(float szerokosc, float wysokosc)
{
	font.loadFromFile("cz/arial.ttf");
	
	MENU_T[0].setFont(font);
	MENU_T[0].setFillColor(sf::Color::Red);
	MENU_T[0].setString("Play");
	MENU_T[0].setPosition(sf::Vector2f(szerokosc / 2, wysokosc / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	MENU_T[1].setFont(font);
	MENU_T[1].setFillColor(sf::Color::White);
	MENU_T[1].setString("idk co tu");
	MENU_T[1].setPosition(sf::Vector2f(szerokosc / 2, wysokosc / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	MENU_T[2].setFont(font);
	MENU_T[2].setFillColor(sf::Color::White);
	MENU_T[2].setString("Exit");
	MENU_T[2].setPosition(sf::Vector2f(szerokosc / 2, wysokosc / (MAX_NUMBER_OF_ITEMS+1) * 3));

	SelectedItem = 0;
}
menu::~menu()
{

}
void menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(MENU_T[i]);
	}
}
void menu::MoveUp()
{
	if (SelectedItem -1 >= 0)
	{
		MENU_T[SelectedItem].setFillColor(sf::Color::White);
		SelectedItem--;
		MENU_T[SelectedItem].setFillColor(sf::Color::Red);
	}
}
void menu::MoveDown()
{
	if (SelectedItem + 1 < MAX_NUMBER_OF_ITEMS)
	{
		MENU_T[SelectedItem].setFillColor(sf::Color::White);
		SelectedItem++;
		MENU_T[SelectedItem].setFillColor(sf::Color::Red);
	}
}