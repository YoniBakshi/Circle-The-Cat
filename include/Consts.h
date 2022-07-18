#pragma once

const float PIC_SIZE	  = 80.f;

const int WINDOW_WIDTH    = 1920;
const int WINDOW_HEIGHT   = 1080;

const int MIN_RANGE		  = 1;
const int MAX_RANGE		  = 3;

const int MAX_TILE		  = 11;

const int MIN_WIDTH_BOARD = 0;
const int MAX_WIDTH_BOARD = 10;

const int RESET_LEVEL	  = 1;
const int MIN_FLIPPED	  = 4;
const int MAX_FLIPPED	  = 14;

const int RESET_INDEX	  = 0;
const int UNDO_INDEX	  = 1;

const int CAT_INDEX		  = 0;
const int TILE_INDEX	  = 1;
const int FLIPPED_INDEX	  = 2;
const int BLOCKED		  = MAX_TILE * MAX_TILE;
const int UNINITIALIZE	  = -1;
const int WIN			  = 555;

// Moving parameters
const auto NEIGHBOR_ABOVE_RIGHT = sf::Vector2i( { 1, -1 } );
const auto NEIGHBOR_ABOVE_LEFT  = sf::Vector2i( { -1, -1 } );
const auto NEIGHBOR_BELOW_RIGHT = sf::Vector2i( { 1, 1 } );
const auto NEIGHBOR_BELOW_LEFT  = sf::Vector2i( { -1, 1 } );
const auto UP					= sf::Vector2i( { 0, -1 } );
const auto LEFT					= sf::Vector2i( {-1, 0} );
const auto DOWN					= sf::Vector2i( { 0, 1 } );
const auto RIGHT				= sf::Vector2i( { 1, 0 } );

//Calculation to focus all objects in center
const float boardGameWidthSpace  = (WINDOW_WIDTH - (MAX_TILE * PIC_SIZE) + PIC_SIZE) / 2.f;
const float boardGameHeightSpace = (WINDOW_HEIGHT - (MAX_TILE * PIC_SIZE)) / 2.f;

const float m_increaseButton = 1.2f;
const float m_originalButton = 1.0f;

const sf::Color m_nonTransparent	= sf::Color(255, 255, 255);
const sf::Color m_partlyTransparent = sf::Color(255, 255, 255, 150);

enum class Buttons
{
	b_Start,
	b_Exit,
	b_Undo,
	b_Reset,
	b_Total
};