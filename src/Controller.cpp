#include "Controller.h"

Controller::Controller()
	: m_isRunning(false),
	m_window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Circle The Cat - Yehonatan Bakshi & Hila Saadon"),
	m_menu(m_window)
{
	m_levelUpMsg.setTexture(Resources::instance().getTexture(Resources::t_LevelUpMsg));
	m_loseMsg.setTexture(Resources::instance().getTexture(Resources::t_LoseMsg));
	m_winMsg.setTexture(Resources::instance().getTexture(Resources::t_WinMsg));
	m_backGround.setTexture(Resources::instance().getTexture(Resources::t_GameBackground));

	m_loseSound.setBuffer(Resources::instance().getSoundBuffer(Resources::Sounds::s_LoseCartoon));
	m_victory.setBuffer(Resources::instance().getSoundBuffer(Resources::Sounds::s_Victory));
	m_byeBye.setBuffer(Resources::instance().getSoundBuffer(Resources::Sounds::s_ByeBye));
	m_lvlUpSound.setBuffer(Resources::instance().getSoundBuffer(Resources::Sounds::s_Yay));
}

void Controller::run()
{
	while (m_window.isOpen())
	{
		runMenu();
		runGame();
	}
}

void Controller::runMenu()
{
	m_menu.resetMenu();

	while ((m_window.isOpen()) && (m_menu.isMenuRunning()))
	{
		m_window.clear();
		m_menu.drawMenu(m_window);
		m_window.display();
		m_menu.resetMenu();
		m_menu.handleMouseEvents(m_window);
	}
}

void Controller::runGame()
{
	m_board.playGameMusic();
	m_board.updateLevel();

	while (m_window.isOpen())
	{
		if (!m_board.isLose())
		{
			if (m_board.isLvlUp())
			{
				m_board.updateLevel();
				// Win game
				if (m_board.isLvlUp())
				{
					m_isRunning = true;
					break;
				}
				// Level up
				m_lvlUpSound.play();
				gameMessage();
			}
			
			draw();
			handleEvents();
		}
		else
		{
			draw();
			sf::sleep(sf::seconds(1));
			gameMessage();
			m_board.gameOver();
		}
	}

	gameMessage();
	Resources::instance().getGameMusic().stop();
	Resources::instance().getMenuMusic().play();
	m_isRunning = false;
}

void Controller::draw()
{
	m_window.clear(); 
	m_window.draw(m_backGround);
	m_board.drawBoard(m_window);
	m_window.display();
}

void Controller::handleEvents()
{
	for (auto event = sf::Event(); m_window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
				break;
			}

		case sf::Event::Closed:
			m_byeBye.play();
			Resources::instance().getMenuMusic().stop();
			Resources::instance().getGameMusic().stop();
			m_window.close();
			break;

		case sf::Event::MouseButtonReleased:
			m_board.handleClick(event.mouseButton);
			break;

		case sf::Event::MouseMoved:
			m_board.handleMove(event.mouseMove);
			break;
		}
	}
}

void Controller::gameMessage()
{
	if (m_isRunning)
	{
		m_victory.play();
		m_window.draw(m_winMsg);
		m_window.display();
		sf::sleep(sf::seconds(3));	//Sleep for 3 seconds so texture will stay on screen
		m_isRunning = false;
		return;
	}

	if (!m_board.isLose())
	{
		m_window.draw(m_levelUpMsg);
		m_window.display();
		sf::sleep(sf::seconds(3));	//Sleep for 3 seconds so texture will stay on screen
		return;
	}

	if (m_board.isLose())
	{
		m_loseSound.play();
		m_window.draw(m_loseMsg);
		m_window.display();
		sf::sleep(sf::seconds(3));	//Sleep for 3 seconds so texture will stay on screen
		return;
	}
}