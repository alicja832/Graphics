//Uwaga! Co najmniej C++17!!!
//Project-> ... Properties->Configuration Properties->General->C++ Language Standard = ISO C++ 17 Standard (/std:c++17)

#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>

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

void Sokoban::LoadMapFromFile(std::string fileName)
{
	std::string str;
	std::vector<std::string> vos;

	std::ifstream in(fileName.c_str());
	while (std::getline(in, str)) { vos.push_back(str); }
	in.close();

	map.clear();
	map.resize(vos.size(), std::vector<Field>(vos[0].size()));
	for (auto[row, row_end, y] = std::tuple{ vos.cbegin(), vos.cend(), 0 }; row != row_end; ++row, ++y)
		for (auto[element, end, x] = std::tuple{ row->begin(), row->end(), 0 }; element != end; ++element, ++x)
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
	// Tu niew¹tpliwie powinno coœ byæ : -) Tu nale¿y narysowaæ wszystko. O tak jakoœ :
	//target.draw(....);

	sf::Texture tex;
	sf::Sprite sprite;
	//sprite.GetSize();
	//Przydatna mo¿e byæ pêtla :
	for (int y = 0; y < map.size(); ++y)
		for (int x = 0; x < map[y].size(); ++x)
		{
			//std::cout << static_cast<std::underlying_type<Field>::type>(map[y][x]) << std::endl;

			//std::cout << (map[y][x]).value << " ";
			//Teraz map[y][x] mówi nam CO mamy narysowaæ.
			switch (map[y][x])
			{
			case Field::WALL:
				if (!tex.loadFromFile("images/wall.png"))
				{
					std::cout << "wall";
					return;
				}
				break;
			case Field::VOID:
				if (!tex.loadFromFile("images/void.png"))
				{
					std::cout << "void";
					return;
				}
				break;
			case Field::FLOOR:
				if (!tex.loadFromFile("images/floor.png"))
				{
					std::cout << "floor";
					return;
				}
				break;
			case Field::BOX:
				if (!tex.loadFromFile("images/box.png"))
				{
					std::cout << "wall";
					return;
				}
				break;
			case Field::PARK:
				if (!tex.loadFromFile("images/park.png"))
				{
					std::cout << "wall";
					return;
				}
				break;
			case Field::PLAYER:
				if (!tex.loadFromFile("images/player.png"))
				{
					std::cout << "wall";
					return;
				}
				break;
			}
			sprite.setTexture(tex);
			sprite.setScale(1.f*tile_size.x / tex.getSize().x, 1.f*tile_size.y / tex.getSize().y);
			sprite.setPosition(shift.x+tile_size.x*x, shift.y+tile_size.y*y);
			target.draw(sprite);


		}
	//std::cout << std::endl;
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
	bool allow_move = false; // Pesymistyczne za³ó¿my, ¿e gracz nie mo¿e siê poruszyæ.
	sf::Vector2i new_pp(player_position.x + dx, player_position.y + dy); //Potencjalna nowa pozycja gracza.
	Field fts = map[new_pp.y][new_pp.x]; //Element na miejscu na które gracz zamierza przejœæ.
	Field ftsa = map[new_pp.y + dy][new_pp.x + dx]; //Element na miejscu ZA miejscem na które gracz zamierza przejœæ. :-D

	//Gracz mo¿e siê poruszyæ jeœli pole na którym ma stan¹æ to pod³oga lub miejsce na skrzynki.
	if (fts == Field::FLOOR || fts == Field::PARK) allow_move = true;
	//Jeœli pole na które chce siê poruszyæ gracz zawiera skrzynkê to mo¿e siê on poruszyæ jedynie jeœli kolejne pole jest puste lub zawiera miejsce na skrzynkê  - bo wtedy mo¿e przepchn¹æ skrzynkê.
	if (fts == Field::BOX && (ftsa == Field::FLOOR || ftsa == Field::PARK))
	{
		allow_move = true;
		//Przepychamy skrzynkê.
		map[new_pp.y + dy][new_pp.x + dx] = Field::BOX;
		//Oczywiœcie pole na którym sta³a skrzynka staje siê teraz pod³og¹.
		map[new_pp.y][new_pp.x] = Field::FLOOR;
	}

	if (allow_move)
	{
		//Przesuwamy gracza.
		map[player_position.y][player_position.x] = Field::FLOOR;
		player_position = new_pp;
		map[player_position.y][player_position.x] = Field::PLAYER;
	}

	//Niestety w czasie ruchu mog³y „ucierpieæ” miejsca na skrzynkê. ;-(
	for (auto park_position : park_positions) if (map[park_position.y][park_position.x] == Field::FLOOR) map[park_position.y][park_position.x] = Field::PARK;
}

bool Sokoban::Is_Victory() const
{
	//Tym razem dla odmiany optymistycznie zak³adamy, ¿e gracz wygra³.
	//No ale jeœli na którymkolwiek miejscu na skrzynki nie ma skrzynki to chyba za³o¿enie by³o zbyt optymistyczne... : -/
	for (auto park_position : park_positions) if (map[park_position.y][park_position.x] != Field::BOX) return false;
	return true;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	sf::CircleShape shape(window.getSize().x/2);
	shape.setFillColor(sf::Color::Green);

	sf::Clock clock;
	sf::Text time_clock;
	time_clock.setPosition(10.0f, 10.0f);


	time_clock.setCharacterSize(80);
	time_clock.setFillColor(sf::Color::Red);

	sf::Text text;

	sf::Font font;
	if (!font.loadFromFile("garota_bonita.ttf"))
	{
		// error...
	}
	// select the font
	text.setFont(font); // font is a sf::Font


	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	
		// inside the main loop, between window.clear() and window.display()
	while (window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();
		int time = elapsed.asSeconds();
		std::string s_time = std::to_string(time);
		time_clock.setString(s_time);
		// set the string to display
		text.setString(std::to_string(time));
		window.clear();
		window.draw(text);
		window.display();

	}

	return 0;
	Sokoban sokoban;
	
	sokoban.LoadMapFromFile("plansza.txt");
	sokoban.SetDrawParameters(window.getSize());


	//06-Tekstury i sprajty

	sf::Event event;
	sf::Texture texture, tex2;
	sf::Sprite sprite, spr2;
	float x, y, t = 0.0;

	window.setVerticalSyncEnabled(true);

	texture.loadFromFile("eye2.jpg");
	sprite.setTexture(texture);
	//brick.setTexture(texture);

	tex2.loadFromFile("transparent.png");
	spr2.setTexture(tex2);
	spr2.setPosition(300, 200);

	//END - 06-Tekstury i sprajty

	//my

	sf::Texture tex;
	if (!tex.loadFromFile("images/wall.png"))
	{
		return 0;
	}

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
			//Oczywiœcie tu powinny zostaæ jakoœ obs³u¿one inne zdarzenia.Na przyk³ad jak gracz naciœnie klawisz w lewo powinno pojawiæ siê wywo³anie metody :
			//sokoban.Move_Player_Left();
			//W dowolnym momencie mog¹ Pañstwo sprawdziæ czy gracz wygra³:
			//sokoban.Is_Victory();


		}
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		//06

		x = 250.0f * sin(0.83f * t) + 250.0f;
		y = 150.0f * cos(0.33f * t) + 150.0f;
		t = t + 0.05f;
		sprite.setPosition(x, y);
		window.draw(sprite);

		spr2.setColor(sf::Color(127.5f * (1.0f + cos(0.25f * t)), 255.0f, 255.0f));


		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.draw(spr2);
		//window.draw(sprite);
		//END 06

		window.draw(sokoban);
		//window.draw(shape);
		window.display();
	}
	
	return 0;
}