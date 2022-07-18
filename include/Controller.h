#pragma once 

#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Board.h"
#include "Consts.h"
#include "GameObject.h"

class Controller
{
public:
	Controller();
	~Controller() = default;

	void run();

private:
	void runMenu();
	void runGame();
	void gameMessage();
	void draw();
	void handleEvents();

	bool m_isRunning;

	sf::RenderWindow m_window;
	sf::CircleShape m_circle;

	Board m_board;
	Menu m_menu;

	sf::Sprite m_winMsg;
	sf::Sprite m_loseMsg;
	sf::Sprite m_levelUpMsg;
	sf::Sprite m_backGround;

	sf::Sound  m_byeBye;
	sf::Sound  m_victory;
	sf::Sound  m_loseSound;
	sf::Sound  m_lvlUpSound;
};



