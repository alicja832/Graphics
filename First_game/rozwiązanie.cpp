//Uwaga! Co najmniej C++17!!!
//Project-> ... Properties->Configuration Properties->General->C++ Language Standard = ISO C++ 17 Standard (/std:c++17)

#include "SFML/Graphics.hpp"
#include <fstream>
#include <vector>

enum class Field { VOID, FLOOR, WALL, BOX, PARK, PLAYER };

class Sokoban : public sf::Drawable
{
public:
	void LoadMapFromFile(std::string fileName);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void SetDrawParameters(sf::Vector2u draw_area_size);
	void Move_Player_Left();
	void Move_Player_Right();
	void Move_Player_Up();
	void Move_Player_Down();
	bool Is_Victory() const;

private:
	std::vector<std::vector<Field>> map;
	sf::Vector2f shift, tile_size;
	sf::Vector2i player_position;
	std::vector<sf::Vector2i> park_positions;

	void move_player(int dx, int dy);
};
//obsługa zdarzeń związanych z wciskaniem klawiszy oraz – najtrudniejsze – uzupełnienie metody 
//Sokoban::draw(…).
void Sokoban::LoadMapFromFile(std::string fileName)
{
	std::string str;
	std::vector<std::string> vos;

	std::ifstream in(fileName.c_str());
	while (std::getline(in, str)) { vos.push_back(str); }
	in.close();

	map.clear();
	map.resize(vos.size(), std::vector<Field>(vos[0].size()));
	for (auto [row, row_end, y] = std::tuple{ vos.cbegin(), vos.cend(), 0 }; row != row_end; ++row, ++y)
		for (auto [element, end, x] = std::tuple{ row->begin(), row->end(), 0 }; element != end; ++element, ++x)
			switch (*element)
			{
			case 'X': map[y][x] = Field::WALL; break;
			case '*': map[y][x] = Field::VOID; break;
			case ' ': map[y][x] = Field::FLOOR; break;
			case 'B': map[y][x] = Field::BOX; break;
			case 'P': map[y][x] = Field::PARK; park_positions.push_back(sf::Vector2i(x, y));  break;
			case 'S': map[y][x] = Field::PLAYER; player_position = sf::Vector2i(x, y);  break;
			}
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Tu niewątpliwie powinno coś być : -) Tu należy narysować wszystko. O tak jakoś :
	//target.draw(....);
	//czyszczenie okna aby mogla sie pojawic dopasowana do rozmiaru okna plansza
	target.clear();

	//tablica zawieracjąca tekstury obrazkow (sreeny elementow gry z demo.)
	sf::Texture area[6];
	sf::Sprite area_spr[6];
	for (int i = 0; i < 6; i++)
	{
		if(i == 0)
			area[0].loadFromFile("Player.png");
		if(i == 1)
			area[1].loadFromFile("Park.png");
		if(i == 2)
			area[2].loadFromFile("Box.png");
		if(i == 3)
			area[3].loadFromFile("Floor.png");
		if(i == 4)
			area[4].loadFromFile("Void.png");
		if(i == 5)
			area[5].loadFromFile("Wall.png");

		//ustawienie tekstur dla każdego elementu
		area_spr[i].setTexture(area[i]);
		//modyfikacja rozmiaru w zaleznosci od rozmiaru okna
		area_spr[i].scale(tile_size.x / area[i].getSize().x, tile_size.y / area[i].getSize().y);
	}

	//Przydatna może być pętla :
	for (int y = 0 ; y < map.size(); ++y)
		for (int x = 0; x < map[y].size(); ++x)
		{
			if (map[y][x] == Field::PLAYER)
			{
				area_spr[0].setPosition(shift.x + x * tile_size.x, shift.y + y * tile_size.y);
				target.draw(area_spr[0]);
			}
			if (map[y][x] == Field::PARK)
			{
				area_spr[1].setPosition(shift.x + x * tile_size.x, shift.y + y * tile_size.y);
				target.draw(area_spr[1]);
			}
			if (map[y][x] == Field::VOID)
			{
				area_spr[4].setPosition(shift.x + x * tile_size.x, shift.y + y * tile_size.y);
				target.draw(area_spr[4]);
			}
			if (map[y][x] == Field::WALL)
			{
				area_spr[5].setPosition(shift.x + x * tile_size.x, shift.y + y * tile_size.y);
				target.draw(area_spr[5]);
			}
			if (map[y][x] == Field::BOX)
			{
				area_spr[2].setPosition(shift.x + x * tile_size.x, shift.y + y * tile_size.y);
				target.draw(area_spr[2]);
			}
			if (map[y][x] == Field::FLOOR)
			{
				area_spr[3].setPosition(shift.x + x * tile_size.x, shift.y + y * tile_size.y);
				target.draw(area_spr[3]);
			}



			//Teraz map[y][x] mówi nam CO mamy narysować.
		}
}

void Sokoban::SetDrawParameters(sf::Vector2u draw_area_size)
{
	this->tile_size = sf::Vector2f(
		std::min(std::floor((float)draw_area_size.x / (float)map[0].size()), std::floor((float)draw_area_size.y / (float)map.size())),
		std::min(std::floor((float)draw_area_size.x / (float)map[0].size()), std::floor((float)draw_area_size.y / (float)map.size()))
	);
	this->shift = sf::Vector2f(
		((float)draw_area_size.x - this->tile_size.x * map[0].size()) / 2.0f,
		((float)draw_area_size.y - this->tile_size.y * map.size()) / 2.0f
	);
}

void Sokoban::Move_Player_Left()
{
	move_player(-1, 0);
}

void Sokoban::Move_Player_Right()
{
	move_player(1, 0);
}

void Sokoban::Move_Player_Up()
{
	move_player(0, -1);
}

void Sokoban::Move_Player_Down()
{
	move_player(0, 1);
}

void Sokoban::move_player(int dx, int dy)
{
	bool allow_move = false; // Pesymistyczne załóżmy, że gracz nie może się poruszyć.
	sf::Vector2i new_pp(player_position.x + dx, player_position.y + dy); //Potencjalna nowa pozycja gracza.
	Field fts = map[new_pp.y][new_pp.x]; //Element na miejscu na które gracz zamierza przejść.
	Field ftsa = map[new_pp.y + dy][new_pp.x + dx]; //Element na miejscu ZA miejscem na które gracz zamierza przejść. :-D

	//Gracz może się poruszyć jeśli pole na którym ma stanąć to podłoga lub miejsce na skrzynki.
	if (fts == Field::FLOOR || fts == Field::PARK) allow_move = true;
	//Jeśli pole na które chce się poruszyć gracz zawiera skrzynkę to może się on poruszyć jedynie jeśli kolejne pole jest puste lub zawiera miejsce na skrzynkę  - bo wtedy może przepchnąć skrzynkę.
	if (fts == Field::BOX && (ftsa == Field::FLOOR || ftsa == Field::PARK))
	{
		allow_move = true;
		//Przepychamy skrzynkę.
		map[new_pp.y + dy][new_pp.x + dx] = Field::BOX;
		//Oczywiście pole na którym stała skrzynka staje się teraz podłogą.
		map[new_pp.y][new_pp.x] = Field::FLOOR;
	}

	if (allow_move)
	{
		//Przesuwamy gracza.
		map[player_position.y][player_position.x] = Field::FLOOR;
		player_position = new_pp;
		map[player_position.y][player_position.x] = Field::PLAYER;
	}

	//Niestety w czasie ruchu mogły „ucierpieć” miejsca na skrzynkę. ;-(
	for (auto park_position : park_positions) if (map[park_position.y][park_position.x] == Field::FLOOR) map[park_position.y][park_position.x] = Field::PARK;
}

bool Sokoban::Is_Victory() const
{
	//Tym razem dla odmiany optymistycznie zakładamy, że gracz wygrał.
	//No ale jeśli na którymkolwiek miejscu na skrzynki nie ma skrzynki to chyba założenie było zbyt optymistyczne... : -/
	for (auto park_position : park_positions) if (map[park_position.y][park_position.x] != Field::BOX) return false;
	return true;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	Sokoban sokoban;

	sf::Clock clock;
	//zmienne potrzebne do utworzenia napisów koncowych
	sf::Font font1;
	sf::Text time_clock,exit,victory,time_victory;
	int time_esc = 0;

	font1.loadFromFile("Freshman.ttf");

	time_clock.setFont(font1);
	time_clock.setPosition(10.0f,10.0f);
	time_clock.setCharacterSize(60.0f);
	time_clock.setFillColor(sf::Color::Red);

	exit.setFont(font1);
	exit.setString("Do you give up?");
	exit.setPosition(100.0f, window.getSize().y / 2.0);
	exit.setCharacterSize(80.0f);
	exit.setFillColor(sf::Color::Black);

	victory.setFont(font1);
	victory.setString("You win! Your time is: ");
	victory.setPosition(20.0f,window.getSize().y / 3.0 );
	victory.setCharacterSize(60.0f);
	victory.setFillColor(sf::Color::Black);

	time_victory.setFont(font1);
	time_victory.setPosition(window.getSize().x - 100.0f, window.getSize().y -100.0f);
	time_victory.setCharacterSize(50.0f);
	time_victory.setFillColor(sf::Color::Black);



	sokoban.LoadMapFromFile("plansza.txt");
	sokoban.SetDrawParameters(window.getSize());

	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			

			if (event.type == sf::Event::Resized)
			{
				float width = static_cast<float>(event.size.width);
				float height = static_cast<float>(event.size.height);
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				sokoban.SetDrawParameters(window.getSize());

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				sokoban.Move_Player_Left();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				sokoban.Move_Player_Right();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				sokoban.Move_Player_Up();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				sokoban.Move_Player_Down();
			}
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{	
				time_esc = clock.getElapsedTime().asSeconds();
				break;
			}
			if (sokoban.Is_Victory())
			{
				time_esc = clock.getElapsedTime().asSeconds();
				break;
			}


			//Oczywiście tu powinny zostać jakoś obsłużone inne zdarzenia.Na przykład jak gracz naciśnie klawisz w lewo powinno pojawić się wywołanie metody :
			//sokoban.Move_Player_Left();
			//W dowolnym momencie mogą Państwo sprawdzić czy gracz wygrał:
			//sokoban.Is_Victory();
		}
		window.draw(sokoban);


		if (event.key.code == sf::Keyboard::Escape)
		 {
			
				window.draw(exit);
				if(clock.getElapsedTime().asSeconds() > time_esc + 4)
					window.close();
		}
		

		if (!sokoban.Is_Victory())
		{
			sf::Time elapsed1 = clock.getElapsedTime();
			std::string s_time = std::to_string(static_cast<int>(elapsed1.asSeconds()));
			time_clock.setString(s_time);
			window.draw(time_clock);
		}
		
		if (sokoban.Is_Victory())
		{

			time_victory.setString(std::to_string(static_cast<int>(time_esc)));
			window.draw(victory);
			window.draw(time_victory);

			if (clock.getElapsedTime().asSeconds() > time_esc + 4)
				window.close();

		}
		
		
		window.display();


	}

	return 0;
}