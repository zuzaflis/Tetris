#pragma once
#include "SFML/Graphics.hpp"
#include <stdlib.h>

#define MAX_NUMBER_OF_ITEMS 3

class menu
{
public:
	menu(float szerokosc, float wysokosc);
	~menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int Wcisniety() { return SelectedItem; }
	
	
private:
	int SelectedItem;
	sf::Font font;
	sf::Text MENU_T[MAX_NUMBER_OF_ITEMS];

};