#pragma once
#include <format>
#include <vector>

#include "Button.h"

class Menu
{
public:
	Menu(const sf::RenderWindow& window);
	~Menu();

	void drawMenu(sf::RenderWindow& window) const;
	void updateMenu(sf::Vector2f& point);
	void resetMenu();
	void handleClick(sf::RenderWindow& window, const Button& buttonClicked);
	bool isMenuRunning()					const;
	void handleMouseEvents(sf::RenderWindow& window);

private:
	std::vector<std::unique_ptr<Button>> m_buttons;
	sf::RectangleShape					 m_menuBackground;
	sf::Sound							 m_buttonSound;
	sf::Sound							 m_byeBye;
	sf::Text							 m_createdBy;

	bool m_isRunning;
};

