#include "Tile.h"

Tile::Tile(sf::Vector2f& position, int index)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::t_Tile));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(position);
	m_isClean = true;
	m_index = index;
}

Tile::~Tile()
{
}
