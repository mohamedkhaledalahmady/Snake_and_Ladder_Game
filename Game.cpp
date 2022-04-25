#include "Game.h"

void Game::Init_Window()
{
	srand(time(0));
	this->videomode.width = 848;// 728;
	this->videomode.height = 650;// 606;
	this->player_width = Image_Width/6;
	this->player_height = Image_Hight/5;
	this->player_radius = Image_Width/12.0f;
	this->Window = new sf::RenderWindow(this->videomode, "Snake and Ladder",sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	this->CreatShape1();
	this->CreatShape2();
	this->background.loadFromFile("C:/Users/MG/source/repos/SFML/background.jpg");
	this->s = new sf::Sprite(this->background);
	if(!this->font.loadFromFile("E:/fonts/Open_Sans/OpenSans-SemiBoldItalic.ttf"))
		printf("Error!!\n");
	this->text.setFont(this->font);
	this->button1 = new Button("Click me :)", { 100,40 }, { 738,152 }, 30, sf::Color::Green, sf::Color::Black);
}
Game::Game()
{
	this->Init_Window();
	printf("Start Game\n");
}
bool Game::running()
{
	return this->Window->isOpen();
}
void Game::pollEvent()
{
	while (this->Window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->Window->close();
			exit(0);
			break;
		case sf::Event::TextEntered:
			printf("%c\n", this->ev.text.unicode);
			//A --> 65 , a --> 97 , Escape --> 27
			if (this->ev.text.unicode == escape)
			{
				this->Window->close();
				exit(0);
			}
		case sf::Event::MouseMoved:
			if (this->button1->isMouseOver(this->Window))
				this->button1->setBackColor(sf::Color(0,255,255,255));
			else
				this->button1->setBackColor(sf::Color::Black);
			break;
		}
	}
}
void Game::update()
{
	this->pollEvent();
}   
void Game::rander(int dice_value)
{
	this->Window->clear(sf::Color::White);
	this->Window->draw(*this->s);
	this->Window->draw(*this->player1);
	this->Window->draw(*this->player2);
	this->text.setPosition((5.0f / 6.0f) * Image_Width/2, Image_Hight);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString("Dice Value: ");
	this->Window->draw(this->text);
	this->text.setPosition((5.0f / 6.0f) * Image_Width / 2  + 155.0f, Image_Hight);
	this->text.setFillColor(sf::Color::Magenta);
	this->text.setString(this->intToChar(dice_value));
	this->Window->draw(this->text);
	this->button1->drawTo(this->Window);
	this->Window->display();
}
void Game::CreatShape1()
{
	this->player1 = new sf::CircleShape(this->player_radius);
	this->player1->setFillColor(sf::Color(0,255,255,255));
	sf::Texture b;
	b.loadFromFile("C:/Users/MG/source/repos/SFML/Walk4Frames.png");
	this->player1->setTexture(&b);
	this->player1->setPosition(0, Image_Hight - this->player_height);//H - H/5 = 4/5 H
}
void Game::CreatShape2()
{
	this->player2 = new sf::CircleShape(player_radius);
	this->player2->setFillColor(sf::Color(0,0,0,255));
	sf::Texture b;
	b.loadFromFile("C:/Users/MG/source/repos/SFML/background.jpg");
	this->player2->setTexture(&b);
	this->player2->setPosition(0, Image_Hight - this->player_height);
}
sf::Vector2f Game::getplayer1_pos()
{
	return this->player1->getPosition();
}
sf::Vector2f Game::getplayer2_pos()
{
	return this->player2->getPosition();
}
void Game::mov_player1_to(int n)
{
	n = n > 30 ? 30 : n;
	int index = (n % 6 == 0 ? (n / 6) : (n / 6) + 1);
	sf::Vector2f v;
	int w1 = index > 1 ? n - 6 * (index-1) : n;
	v.x = index % 2 == 1 ? (w1 % 7 -1)*this->player_width : Image_Width - (w1 % 7) * this->player_width;
	v.y = Image_Hight - index*this->player_height;
	//printf("n: %d\nindex: %d\nv.x: %f\nv.y: %f\n", n, index, v.x, v.y);
	this->player1->setPosition(v.x, v.y);
}
void Game::mov_player2_to(int n)
{
	int index = (n % 6 == 0 ? (n / 6) : (n / 6) + 1);
	sf::Vector2f v;
	int w1 = index > 1 ? n - 6 * (index - 1) : n;
	v.x = index % 2 == 1 ? (w1 % 7 - 1) * this->player_width : Image_Width - (w1 % 7) * this->player_width;
	v.y = Image_Hight - index * this->player_height;
	//printf("n: %d\nindex: %d\nv.x: %f\nv.y: %f\n", n, index, v.x, v.y);
	this->player2->setPosition(v.x, v.y);
}
void Game::delay(int sec)
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(10 * sec));
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(sec));
}
int Game::dice()
{
	return ((rand() % 6) + 1);
}
char Game::intToChar(int n)
{
	return n + '0';
}
Game::~Game()
{
	printf("End Game\n");
}