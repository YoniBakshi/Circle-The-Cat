#pragma once

#include <ctime>
#include <stack>
#include <queue>
#include <vector>
#include <format>
#include <random>
#include <cstdlib>
#include <algorithm>

#include "Cat.h"
#include "Tile.h"
#include "Button.h"
#include "Resources.h"
#include "GameObject.h"

class Board
{
public:
	Board();
	~Board() = default;

	void drawBoard(sf::RenderWindow& window);
	void updateLevel();					
	void handleClick(const sf::Event::MouseButtonEvent& event);
	void handleMove(const sf::Event::MouseMoveEvent& event);
	void gameOver();
	void playGameMusic() const;
	bool isLvlUp()		 const;
	bool isLose()		 const;

private:
	std::vector<int> getNeighbors(const int position);
	sf::Vector2i cnvert2i(int);

	void resetVariables();
	void creatRandomFlip();
	void createBfsTree();
	void checkMovement();
	void setBoard();
	void lastMove();
	void setCat(sf::Vector2f&, int nextStep);
	void moveCat(int nextStep);
	int covertToInt(sf::Vector2i next);
	int findMin();
	int findPath(int min);
	int moveRandInnerCircle();
	bool inBoard(sf::Vector2i posTo);
	bool checkOutlines(int nextStep);
	bool setLvlUp(int nextStep);

	bool m_isLose;
	bool m_isLvlUp;
	int  m_level;
	int  m_catPos;
	int  m_starterFlipped;

	std::vector<std::unique_ptr<GameObject>> m_vecGameObj;
	std::vector<std::unique_ptr<Button>>	 m_buttons;
	std::vector<sf::Vector2i>				 m_bfsTree;

	std::stack<sf::Vector2i> m_moves;

	sf::RectangleShape m_boardArea;
	sf::CircleShape	   m_shadow;
	sf::Sound		   m_jumpSound;
	sf::Text		   m_clicksText;
	sf::Sprite		   m_undo;
};
