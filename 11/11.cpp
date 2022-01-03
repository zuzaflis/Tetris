#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "menu.h"
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };
bool end = false;
struct Point
{
	int x, y;
} a[4], b[4]; // bufor następny i poprzedni

/// <summary>
/// 0   1
/// 2   3
/// 4   5
/// 6   7
/// </summary>
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};
/// <summary>
/// sprawdzenie kolizji klocków 
/// </summary>
/// <returns>prawda jeśli nie nachodzą</returns>

bool check() 
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0; 


	return 1;
};


int main()
{

	Color colors[] =
	{
	 Color::Black,
	 Color::White,       ///< White predefined color
	 Color::Red,        ///< Red predefined color
	 Color::Green,       ///< Green predefined color
	 Color::Blue,        ///< Blue predefined color
	 Color::Yellow,      ///< Yellow predefined color
	 Color::Magenta,     ///< Magenta predefined color
	 Color::Cyan,

	};

	srand(time(0));

	RenderWindow window(VideoMode(320, 420), "Tetris!");
	menu Menu(window.getSize().x, window.getSize().y);
	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/frame.png");
	t4.loadFromFile("images/gameover.png");

	/// <summary>
	/// wszystkie kafelki
	/// </summary>
	Sprite s(t1);
	Sprite background(t2), frame(t3), gameover(t4);
	gameover.move(10, 50);
	int dx = 0; bool rotate = 0;

	/// <summary>
	/// numer kafelka w teksturze 
	/// </summary>
	int colorNum = 1;
	float timer = 0, delay = 0.3;

	Clock clock;

	while (window.isOpen())//game loop
	{
		
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))// kiedy jest jakis event w naszym oknie sie cos dzieje//okno slucha polecenia eventu
		{

			if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Up)

					Menu.MoveUp();

				if (e.key.code == sf::Keyboard::Down)
				{
					Menu.MoveDown();
				}
			}

			if (e.type == Event::Closed) //e.type kazdy event ma jakis typ 
				window.close();
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape) window.close();

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Up) rotate = true;
				else if (e.key.code == Keyboard::Left) dx = -1;
				else if (e.key.code == Keyboard::Right) dx = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;// jak sie klika dol to przyspiesza a nie opoznia wiec trzeba nazwe zmienic

		//// <- Move -> ///
		for (int i = 0; i < 4; i++)
		{

			b[i] = a[i];

			a[i].x += dx;
		}

		if (!check())
			for (int i = 0; i < 4; i++)
				a[i] = b[i];

		//////Rotate//////
		if (rotate)
		{
			Point p = a[1]; //center of rotation
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y; //musimy znać odległość od środka obrotu i póżniej tę odległość przenosimy na wpółrzędne x albo y
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check())
				for (int i = 0; i < 4; i++) //dlatego jeśli jest za blisko ścian to się nie wykonuje obrót 
					a[i] = b[i];
		}

		///////Tick//////
		if (timer > delay) //wykonuje kiedy minie delay
		{
			for (int i = 0; i < 4; i++)
			{

				b[i] = a[i]; a[i].y += 1;

			}
			timer = 0;
			if (!check())
			{
				for (int i = 0; i < 4; i++)field[b[i].y][b[i].x] = colorNum; //zapisanie do tablicy koloru klocka który jest definiowany niżej

				colorNum = 1 + rand() % 7; //generowanie koloru klocka 

				int n = rand() % 7;   // losowanie figury
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2; //ustalam współrzędne nowej figury
					a[i].y = (int)figures[n][i] / 2;
				}

				if (!check())

				{
					end = true;
					timer = -10e10; //cofam sie w czasie 

				}
			}
		}

		///////check lines//////////
		int k = M - 1;//dlugosc pola, skad spada klocek
		for (int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < N) k--;
		}

		dx = 0; rotate = 0; delay = 0.3;

		/////////draw//////////
		window.clear(Color::Black);
		Menu.draw(window);
		//window.draw(background);


		//RectangleShape rectangle;

		//for (int i = 0; i < M; i++)
		//	for (int j = 0; j < N; j++) //rysowanie klocków, które spadły
		//	{

		//		rectangle.setSize(Vector2f(18, 18));

		//		rectangle.setOutlineColor(Color::Black);
		//		rectangle.setOutlineThickness(1);
		//		if (field[i][j] == 0) continue; //przezroczystość
		//		rectangle.setFillColor(colors[field[i][j]]);
		//		s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18)); //wyciągam kafelka z tekstury
		//		rectangle.setPosition(j * 18, i * 18);
		//		rectangle.move(28, 31); //offset
		//		window.draw(rectangle);

		//	}

		//for (int i = 0; i < 4; i++)
		//{

		//	rectangle.setSize(Vector2f(18, 18));
		//	rectangle.setFillColor(Color::Red);
		//	rectangle.setOutlineColor(Color::Black);
		//	rectangle.setOutlineThickness(1);
		//	rectangle.setPosition(a[i].x * 18, a[i].y * 18);
		//	rectangle.move(28, 31);
		//	window.draw(rectangle);

			//s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			//s.setPosition(a[i].x * 18, a[i].y * 18);
			//s.move(28, 31); //offset // przesunięcie o ramkę 
			//window.draw(s);

	//	}
	//	window.draw(frame);

		if (end)

		{
			window.draw(gameover);
		}


		window.display();
	}

	return 0;

}
