#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Consts.h"

class Resources
{
public:
	enum Fonts
	{
		f_Mangat,
		f_Paw,
		f_Total
	};

	enum Textures
	{
		t_Tile,
		t_Cat,
		t_FlippedTile,
		t_GameBackground,
		t_MenuBackground,
		t_Undo,
		t_Reset,
		t_LevelUpMsg,
		t_LoseMsg,
		t_WinMsg,
		t_Start,
		t_Exit,
		t_Total
	};

	enum class Sounds
	{
		s_ButtonClicked,
		s_JumpCartoon,
		s_LoseCartoon,
		s_Yay,
		s_Victory,
		s_ByeBye,
		s_Total
	};

	~Resources() = default;

	static Resources& instance();
	const sf::Texture& getTexture(int indexType)		const;
	const sf::Font& getFont(int index_type)				const;
	const sf::SoundBuffer& getSoundBuffer(Sounds index) const;
	sf::Music& getMenuMusic();
	sf::Music& getGameMusic();

private:
	//Constructor
	Resources();
	Resources(const Resources&)				= default;
	Resources& operator= (const Resources&) = default;

	void loadFonts();
	void loadTexture();
	void loadSounds();

	std::vector<sf::Font>		 m_font;
	std::vector<sf::Texture>	 m_texture;
	std::vector<sf::SoundBuffer> m_soundBuffer;

	sf::Music m_menuMusic;
	sf::Music m_gameMusic;
};


