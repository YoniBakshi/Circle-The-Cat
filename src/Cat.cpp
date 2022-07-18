#include "Cat.h"

Cat::Cat(sf::Vector2f& position, int index) : Cat()	// Reuse
{
	m_sprite.setPosition(position);
	m_index = index;
}

Cat::Cat()
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_Cat));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_isClean = false;
}

Cat::~Cat()
{
}

void Cat::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}
