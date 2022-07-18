#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Consts.h"

class Button
{
public:
	Button() = default;
	Button(Resources::Textures index, Buttons indexButton);
	~Button();

	void drawButton(sf::RenderWindow& window) const;
	void setPosition(sf::Vector2f pos);
	void resetButtons();
	bool checkContain(sf::Vector2f& point) const;
	void handleContain();
	Buttons getIndexButton() const;

private:
	sf::Sprite m_button;
	Buttons m_indexButton;
};

