#pragma once

#include "GameObject.h"

class Cat : public GameObject
{
public:
	Cat(sf::Vector2f& position, int index);
	Cat();
	~Cat();

	void setPosition(const sf::Vector2f& position);

private:

};

