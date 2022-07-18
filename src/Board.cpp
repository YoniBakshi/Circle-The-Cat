#include "Board.h"

Board::Board()
	: m_catPos(0), m_level(RESET_LEVEL), m_isLose(false), m_isLvlUp(false), m_starterFlipped(MAX_FLIPPED)
{
	m_jumpSound.setBuffer(Resources::instance().getSoundBuffer(Resources::Sounds::s_JumpCartoon));
	m_jumpSound.setVolume(20.f);

	m_buttons.push_back(std::make_unique<Button>(Resources::t_Reset, Buttons::b_Reset));
	m_buttons.push_back(std::make_unique<Button>(Resources::t_Undo, Buttons::b_Undo));

	//Locate menu's buttons on screen
	sf::Vector2f loc(WINDOW_WIDTH / 7.5f, WINDOW_HEIGHT / 2 + 180.f);

	for (int i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i]->setPosition(loc);
		loc.x += 1400;
	}

	m_clicksText.setFont(Resources::instance().getFont(Resources::f_Paw));
	m_clicksText.setCharacterSize(50);

	m_clicksText.setString(std::format("Level : {:70} {} {} ", std::to_string(m_level), "Number of clicks :", m_moves.size()));
	m_clicksText.setPosition(WINDOW_WIDTH / 11.f, WINDOW_HEIGHT / 5);
	m_clicksText.setColor(sf::Color(239, 246, 247, 186));
	m_clicksText.setOutlineColor(sf::Color(23, 131, 143, 186));
	m_clicksText.setOutlineThickness(2.5f);

	//Set details for Rectangle of transparent background of board.
	m_boardArea.setFillColor(sf::Color(200, 217, 220, 110));
	m_boardArea.setSize({ MAX_TILE * PIC_SIZE + 55 , MAX_TILE * PIC_SIZE + 10 });
	m_boardArea.setOrigin(m_boardArea.getGlobalBounds().width / 2, m_boardArea.getGlobalBounds().height / 2);
	m_boardArea.setPosition(WINDOW_WIDTH / 2 + 20, WINDOW_HEIGHT / 2 - boardGameHeightSpace + PIC_SIZE / 1.3f);

	srand(unsigned(time(0)));
}

void Board::drawBoard(sf::RenderWindow& window)
{
	window.draw(m_boardArea);

	for (auto& singleStatic : m_vecGameObj)
		singleStatic->drawObject(window);

	for (auto& i : m_buttons)
		i->drawButton(window);

	window.draw(m_clicksText);
	window.draw(m_shadow);
}

void Board::updateLevel()
{
	while (!m_moves.empty())
		lastMove();

	m_clicksText.setString(std::format("Level : {:76} {} {} ", std::to_string(m_level), "Number of clicks :", m_moves.size()));

	setBoard();
	auto currLoc = m_vecGameObj[m_vecGameObj.size() / 2]->getPosition();
	setCat(currLoc, m_vecGameObj.size() / 2);
	createBfsTree();
	creatRandomFlip();
	m_isLvlUp = false;

	//Check quantity of current flipped, if lower than 4 - User won the game.
	if (m_starterFlipped < MIN_FLIPPED)
		resetVariables();
}

void Board::resetVariables()
{
	m_starterFlipped = MAX_FLIPPED;
	m_level = RESET_LEVEL;
	m_isLose = false;
	m_isLvlUp = true;
}

void Board::setBoard()
{
	m_vecGameObj.clear();
	auto currLoc = sf::Vector2f();

	for (float i = 0; i < MAX_TILE; ++i)			// ROWS
	{
		for (float j = 0; j < MAX_TILE; ++j)		// COLS
		{
			if ((int)i % 2 != 0)
				currLoc = sf::Vector2f(j * PIC_SIZE + boardGameWidthSpace + (PIC_SIZE / 2), i * PIC_SIZE + boardGameHeightSpace);
			else
				currLoc = sf::Vector2f(j * PIC_SIZE + boardGameWidthSpace, i * PIC_SIZE + boardGameHeightSpace);

			m_vecGameObj.push_back(std::make_unique<Tile>(currLoc, MAX_TILE * i + j));
		}
	}
}

void Board::creatRandomFlip()
{
	// Random a number in range of 1-3 to decrease from total amount fliiped in every level up
	if (m_isLvlUp)
		m_starterFlipped -= rand() % MAX_RANGE + MIN_RANGE;

	int index;

	for (int i = 0; i < m_starterFlipped; ++i)
	{
		index = rand() % m_vecGameObj.size();
		if (index == m_vecGameObj.size() / 2)
			--i;
		else
			m_vecGameObj[index]->updateObjects(Resources::t_FlippedTile, false);
	}

	// Term to make sure that level started and available to solve 
	if (index = findMin(); index == -1)
		creatRandomFlip();
}

void Board::gameOver()
{
	while (!m_moves.empty())
		lastMove();

	m_clicksText.setString(std::format("Level : {:76} {} {} ", std::to_string(m_level), "Number of clicks :", m_moves.size()));

	m_bfsTree.clear();
	createBfsTree();
	m_isLose = false;
}

void Board::playGameMusic() const
{
	Resources::instance().getGameMusic().setLoop(true);
	Resources::instance().getGameMusic().setVolume(12.f);
	Resources::instance().getGameMusic().play();
}

void Board::setCat(sf::Vector2f& currLoc, int nextStep)
{
	if (m_vecGameObj.size() > 0)
	{
		m_vecGameObj[nextStep] = std::make_unique<Cat>(currLoc, nextStep);
		m_catPos = nextStep;
	}
}

void Board::moveCat(int nextStep)
{
	if (!m_isLose)
		m_jumpSound.play();

	m_vecGameObj[m_catPos]->updateObjects(Resources::t_Tile, true);
	auto currLoc = m_vecGameObj[nextStep]->getPosition();
	setCat(currLoc, nextStep);
}

bool Board::setLvlUp(int nextStep)
{
	if (nextStep == WIN)
	{
		++m_level;
		m_isLvlUp = true;
		return true;
	}

	return false;
}

int Board::findPath(int min)
{
	while (m_bfsTree[m_bfsTree[min].x].x != UNINITIALIZE)
		min = m_bfsTree[min].x;

	return min;
}

void Board::handleMove(const sf::Event::MouseMoveEvent& event)
{
	auto currLoc = sf::Vector2f(float(event.x), float(event.y));

	for (auto& singleStatic : m_vecGameObj)
	{
		if (singleStatic->checkContain(currLoc) && singleStatic->isClean())
		{
			m_shadow.setOrigin({ 32.f,32.f });
			m_shadow.setPosition(singleStatic->getPosition());
			m_shadow.setFillColor(m_partlyTransparent);
			m_shadow.setRadius(32);
			return;
		}
	}

	m_shadow.setRadius(0);
}

void Board::handleClick(const sf::Event::MouseButtonEvent& event)
{
	auto currLoc = sf::Vector2f(float(event.x), float(event.y));

	for (auto& singleStatic : m_vecGameObj)
	{
		if (singleStatic->checkContain(currLoc))
		{
			if (singleStatic->isClean())
			{
				m_moves.push({ singleStatic->getIndex(), m_catPos });
				singleStatic->updateObjects(Resources::t_FlippedTile, false);
				createBfsTree();
				checkMovement();
			}
		}
	}

	if (m_buttons[RESET_INDEX]->checkContain(currLoc))
		updateLevel();

	if (m_buttons[UNDO_INDEX]->checkContain(currLoc) && m_moves.size() > 0)
		lastMove();

	m_clicksText.setString(std::format("Level : {:76} {} {} ", std::to_string(m_level), "Number of clicks :", m_moves.size()));
}

bool Board::isLose() const
{
	return m_isLose;
}

bool Board::isLvlUp() const
{
	return 	m_isLvlUp;
}

void Board::createBfsTree()
{
	int start = m_vecGameObj[m_catPos]->getIndex();

	m_bfsTree.assign(MAX_TILE * MAX_TILE, sf::Vector2i(UNINITIALIZE, BLOCKED));
	m_bfsTree[start].y = CAT_INDEX;
	// Set a queue to hold cordinate
	std::queue<int> que;
	// Put cordinate in the queue
	que.push(start);

	while (!que.empty())
	{
		// Take a cordinate from the queue
		int current = que.front();

		que.pop();
		// Set a vector of all the legal neighboors
		std::vector<int> neighbors = getNeighbors(current);
		//Check all the neighbors and set them ways
		for (auto& next : neighbors)
		{
			// If it's a good neighbor, set his way
			if ((next != start)
				&& (m_bfsTree[next].y == BLOCKED))
			{
				que.push(next);
				m_bfsTree[next].y = m_bfsTree[current].y + 1;
				m_bfsTree[next].x = current;
			}
		}
	}
}

int Board::findMin()
{
	int min = m_bfsTree[0].y;
	std::vector<int> minVec;

	for (auto i = 0; i < m_bfsTree.size(); i++)
	{
		//Check if Cat reached to board's outlines
		if (checkOutlines(i))
		{
			if (m_bfsTree[i].y < min)
			{
				minVec.erase(minVec.begin(), minVec.end());
				min = m_bfsTree[i].y;
			}

			if (m_bfsTree[i].y == min && m_bfsTree[i].y != BLOCKED)
				minVec.push_back(i);
		}
	}

	if (minVec.size() == 0)
		return -1;

	auto minRandom = rand() % minVec.size();
	return minVec[minRandom];
}

void Board::checkMovement()
{
	int min = findMin();
	int nextStep;

	if (min == -1)
	{
		nextStep = moveRandInnerCircle();

		if (setLvlUp(nextStep))
			return;
	}
	else
		nextStep = findPath(min);

	moveCat(nextStep);
	m_isLvlUp = false;

	if (checkOutlines(nextStep))
		m_isLose = true;
}

int Board::moveRandInnerCircle()
{
	std::vector<int> neighbors = getNeighbors(m_catPos);
	shuffle(neighbors.begin(), neighbors.end(), std::default_random_engine(rand()));
	//Check all neighbors in inner circle and set them ways
	for (auto& next : neighbors)
		if (m_bfsTree[next].x != -1 && m_vecGameObj[next]->isClean())
			return next;

	return WIN;
}

void Board::lastMove()
{
	m_vecGameObj[m_moves.top().x]->updateObjects(Resources::t_Tile, true);
	moveCat(m_moves.top().y);
	m_moves.pop();
}

// This function returns the nieghbors of a certain cell in the board
std::vector<int> Board::getNeighbors(const int position)
{
	sf::Vector2i con = cnvert2i(position);
	// Set vector to hold the result x as row y as col
	std::vector<sf::Vector2i> shifts = { UP, LEFT, DOWN, RIGHT };

	if (con.x % 2 == 0)
	{
		shifts.push_back(NEIGHBOR_ABOVE_RIGHT);
		shifts.push_back(NEIGHBOR_ABOVE_LEFT);
	}
	else
	{
		shifts.push_back(NEIGHBOR_BELOW_RIGHT);
		shifts.push_back(NEIGHBOR_BELOW_LEFT);
	}

	// Set vector to hold the result
	std::vector<int> neighbors;
	sf::Vector2i next;

	for (int i = 0; i < shifts.size(); i++)
	{
		next = con + shifts[i];

		if (inBoard(next) && m_vecGameObj[covertToInt(next)]->isClean())
			neighbors.push_back(covertToInt(next));
	}

	// Return the neighbors
	return neighbors;
}

sf::Vector2i Board::cnvert2i(int position)
{
	return 	sf::Vector2i(m_vecGameObj[position]->getIndex() / MAX_TILE,
		m_vecGameObj[position]->getIndex() % MAX_TILE);
}

int Board::covertToInt(sf::Vector2i next)
{
	return next.x * MAX_TILE + next.y;
}

bool Board::inBoard(sf::Vector2i position)
{
	return !(position.x < 0 || position.x >= MAX_TILE || position.y < 0 || position.y >= MAX_TILE);
}

bool Board::checkOutlines(int nextStep)
{
	return(nextStep / MAX_TILE == MIN_WIDTH_BOARD || nextStep / MAX_TILE == MAX_WIDTH_BOARD ||
		   nextStep % MAX_TILE == MIN_WIDTH_BOARD || nextStep % MAX_TILE == MAX_WIDTH_BOARD);
}

