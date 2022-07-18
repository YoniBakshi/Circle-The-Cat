#include "Resources.h"

Resources::Resources()
{
	loadFonts();
	loadTexture();
	loadSounds();
}

/* Clone the texture so each object will hold a copy of map
 * Be in use when we are needed to erase something from map
 * like Gift / Key / kill Orc.	*/
Resources& Resources::instance()
{
	static Resources instance;
	return instance;
}

const sf::Texture& Resources::getTexture(int indexType) const
{
	return m_texture[indexType];
}

const sf::Font& Resources::getFont(int index_type) const
{
	return m_font[index_type];
}

sf::Music& Resources::getMenuMusic()
{
	return m_menuMusic;
}

sf::Music& Resources::getGameMusic()
{
	return m_gameMusic;
}

const sf::SoundBuffer& Resources::getSoundBuffer(Sounds index) const
{
	return m_soundBuffer[(int)index];
}

void Resources::loadFonts()
{
	m_font.resize(f_Total);
	m_font[f_Mangat].loadFromFile("mangat.ttf");
	m_font[f_Paw].loadFromFile("PuppyBellies.ttf");
}

void Resources::loadTexture()
{
	m_texture.resize(t_Total);
	m_texture[t_Cat].loadFromFile("CatPoro.png");
	m_texture[t_Tile].loadFromFile("Tile.png");
	m_texture[t_FlippedTile].loadFromFile("Flipped.png");
	m_texture[t_GameBackground].loadFromFile("GameBackground.png");
	m_texture[t_MenuBackground].loadFromFile("MenuBackground.png");

	m_texture[t_Start].loadFromFile("Start.png");
	m_texture[t_Exit].loadFromFile("Exit.png");
	m_texture[t_Undo].loadFromFile("Undo.png");
	m_texture[t_Reset].loadFromFile("Reset.png");

	m_texture[t_LevelUpMsg].loadFromFile("LevelUpMsg.png");
	m_texture[t_LoseMsg].loadFromFile("LoseMsg.png");
	m_texture[t_WinMsg].loadFromFile("WinMsg.png");
}

void Resources::loadSounds()
{
	m_soundBuffer.resize((int)Sounds::s_Total);

	m_soundBuffer[(int)Sounds::s_ButtonClicked].loadFromFile("ButtonClick.wav");
	m_soundBuffer[(int)Sounds::s_ByeBye].loadFromFile("ByeBye.wav");
	m_soundBuffer[(int)Sounds::s_Yay].loadFromFile("Yay.wav");
	m_soundBuffer[(int)Sounds::s_JumpCartoon].loadFromFile("JumpCartoonBoing.wav");
	m_soundBuffer[(int)Sounds::s_Victory].loadFromFile("Victory!(LOLAnnouncer)SoundEffect.wav");
	m_soundBuffer[(int)Sounds::s_LoseCartoon].loadFromFile("LoseCartoon.wav");

	m_menuMusic.openFromFile("MenuMusic-MapleStoryLithHarbor-AboveTheTreetops.wav");
	m_gameMusic.openFromFile("GameMusic-MapleStoryKerningCity-BadGuys.wav");
}