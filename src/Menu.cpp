#include "Menu.h"

Menu::Menu(const sf::RenderWindow& window)
	 : m_isRunning(true),
	   m_menuBackground(sf::Vector2f(window.getSize().x, window.getSize().y))
{
	Resources::instance().getMenuMusic().setLoop(true);
	Resources::instance().getMenuMusic().setVolume(25.f);
	Resources::instance().getMenuMusic().play();

	m_buttonSound.setBuffer(Resources::instance().getSoundBuffer(Resources::Sounds::s_ButtonClicked));
	m_byeBye.setBuffer(Resources::instance().getSoundBuffer(Resources::Sounds::s_ByeBye));

	// Set details for menu's buttons
	m_menuBackground.setTexture(&Resources::instance().getTexture(Resources::t_MenuBackground));
	m_buttons.push_back(std::make_unique<Button>(Resources::t_Start, Buttons::b_Start));
	m_buttons.push_back(std::make_unique<Button>(Resources::t_Exit, Buttons::b_Exit));

	// Locate menu's buttons on screen
	sf::Vector2f loc(window.getSize().x / 2 + 300.f, window.getSize().y / 4.5f);
	for (int i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i]->setPosition(loc);
		loc.x -= 400;
		loc.y += 360;
	}

	//Set details for created by line
	m_createdBy.setFont(Resources::instance().getFont(Resources::f_Mangat));
	m_createdBy.setCharacterSize(35);
	m_createdBy.setOutlineThickness(1);
	m_createdBy.setOutlineColor(sf::Color::White);
	m_createdBy.setColor(sf::Color(31, 166, 175, 250));
	m_createdBy.setString(std::format("{:^55}\nYehonatan Bakshi & Hila Saadon", "by:"));
	m_createdBy.setOrigin(m_createdBy.getGlobalBounds().width / 2, m_createdBy.getGlobalBounds().height / 2);
	loc.x += 480;
	loc.y -= 20;
	m_createdBy.setPosition(loc);
}

Menu::~Menu()
{
}

void Menu::drawMenu(sf::RenderWindow& window) const
{
	window.draw(m_menuBackground);
	window.draw(m_createdBy);

	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i]->drawButton(window);
}

void Menu::updateMenu(sf::Vector2f& point)
{
	for (int i = 0; i < m_buttons.size(); ++i)
	{
		if (m_buttons[i]->checkContain(point))	//If the mouse stands on button
			m_buttons[i]->handleContain();

		else
			m_buttons[i]->resetButtons();
	}
}

void Menu::resetMenu()
{
	m_isRunning = true;
}

//A button has been clicked
void Menu::handleClick(sf::RenderWindow& window, const Button& buttonClicked)
{
	switch (buttonClicked.getIndexButton())	//Verify which button was being clicked
	{
	case Buttons::b_Start:
		m_isRunning = false;
		m_buttonSound.play();
		Resources::instance().getMenuMusic().stop();
		break;

	case Buttons::b_Exit:
		m_byeBye.play();
		window.close();
		break;

	default:
		break;
	}
}

bool Menu::isMenuRunning() const
{
	return m_isRunning;
}

void Menu::handleMouseEvents(sf::RenderWindow& window)
{
	sf::Vector2f location;

	for (auto event = sf::Event{}; window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_byeBye.play();
			window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_byeBye.play();
				window.close();
			}
			break;

		case sf::Event::MouseMoved:
			location = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
			updateMenu(location);
			break;

		case sf::Event::MouseButtonReleased:
			location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			for (int i = 0; i < m_buttons.size(); ++i)
			{
				if (m_buttons[i]->checkContain(location))	//If the mouse stands on button
					handleClick(window, *m_buttons[i]);
			}
		}
	}
}