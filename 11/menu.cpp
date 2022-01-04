#include "menu.h"



menu::menu(float szerokosc, float wysokosc)
{
	fontTitle.loadFromFile("cz/LexendDeca-Black.ttf");
	font.loadFromFile("cz/LexendDeca-Regular.ttf");

	m_title.setFont(fontTitle);
	m_title.setString("TETRIS");
	m_title.setCharacterSize(40);
	m_title.setFillColor(sf::Color(100, 115, 47, 250));
	m_title.setOutlineColor(sf::Color::White);
	m_title.setOutlineThickness(1);
	m_title.setPosition(sf::Vector2f(szerokosc / 6, wysokosc / 18));

	MENU_T[0].setFont(font);
	MENU_T[0].setFillColor(sf::Color(100, 115, 47, 250));
	MENU_T[0].setString("Play");
	MENU_T[0].setPosition(sf::Vector2f(szerokosc / 3, wysokosc / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	MENU_T[1].setFont(font);
	MENU_T[1].setFillColor(sf::Color::White);
	MENU_T[1].setString("Rules");
	MENU_T[1].setPosition(sf::Vector2f(szerokosc / 3, wysokosc / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	MENU_T[2].setFont(font);
	MENU_T[2].setFillColor(sf::Color::White);
	MENU_T[2].setString("Exit");
	MENU_T[2].setPosition(sf::Vector2f(szerokosc / 3, wysokosc / (MAX_NUMBER_OF_ITEMS+1) * 3));

	Selected = 0;
}
menu::~menu()
{

}
void menu::draw(sf::RenderWindow &window)
{
	window.draw(m_title);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(MENU_T[i]);
	}
}
void menu::MoveUp()
{
	if (Selected -1 >= 0)
	{
		MENU_T[Selected].setFillColor(sf::Color::White);
		Selected--;
		MENU_T[Selected].setFillColor(sf::Color(100, 115, 47, 250));
	}
}
void menu::MoveDown()
{
	if (Selected + 1 < MAX_NUMBER_OF_ITEMS)
	{
		MENU_T[Selected].setFillColor(sf::Color::White);
		Selected++;
		MENU_T[Selected].setFillColor(sf::Color(100, 115, 47, 250));
	}
}