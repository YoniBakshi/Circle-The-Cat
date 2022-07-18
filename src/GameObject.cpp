#include "GameObject.h"

GameObject::GameObject() : m_isClean(true), m_index(0)
{
}

GameObject::~GameObject()
{
}

void GameObject::drawObject(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

bool GameObject::isClean() const
{
	return m_isClean;
}

int GameObject::getIndex() const
{
	return m_index;
}

void GameObject::updateObjects(Resources::Textures type, bool isClean)
{
	m_sprite.setTexture(Resources::instance().getTexture(type));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);

	m_isClean = isClean;
}

bool GameObject::checkContain(sf::Vector2f pos) const
{
	return m_sprite.getGlobalBounds().contains(pos);
}

void GameObject::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}