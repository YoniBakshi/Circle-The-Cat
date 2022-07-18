#pragma once

#include <SFML/Graphics.hpp>

#include "Consts.h"
#include "Resources.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void setPosition(sf::Vector2f pos);
	void drawObject(sf::RenderWindow& window) const;
	void updateObjects(Resources::Textures type, bool isClean);
	bool isClean()							  const;
	bool checkContain(sf::Vector2f pos)		  const;
	int getIndex()							  const;
	sf::Vector2f getPosition()			  	  const;

protected:
	sf::Sprite m_sprite;
	bool m_isClean;
	int m_index;

private:

};

