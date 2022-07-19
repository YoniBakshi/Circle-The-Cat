============================================================================
"Circle The Cat"

Description : 
This program fulfill the known game "Circle The Cat", or in our case - "Circle The Poro".
The board of the game is made of 11 X 11 tiles, cat always starts in the middle.
The goal of the game is circle the cat by click and flip the tiles so it's way to the outlines will be blocked.
Each tile can be flipped only once in each level.
To level up - the cat needs to be blocked complelty (no available movements at all).
The cat calculates it's shortest path to the outlines of the board by BFS algorithm.

Menu contains the buttons :
1. Start the game.
2. Exit.

Board screen contains :
1. The game board itself.
2. Details : number of current level and quantity of clicks in current level.
3. Reset button - By clicking it the level will be restarted. NOTE : Quantity of flipped tiles will stay the same.
4. Undo button - Each click will reverse one move backwards - including cat movement and flipped tile. (Can be reversed to beginning of the level.)

Cat = Furry thingy with pink glasses looks like a unicorn
Blue tile = Available tile of a path.
Gold tile = Flipped tile which is blocked.

==============================================================================

Data Structure :
Using stack for "Undo" button to pop the last move.
Using queue for BFS algorithm.
Using vectors to game board, buttons and so on...

==============================================================================

Algorithms :
1. The order of the flipped tiles in the beginning of every new level is completly random - using "rand" to choose which tiles
    to flip in the vector of board's tiles.
2. The quantity of flipped tiles in every level is random and being decrease randomly in every progress in levels.
    Using "rand" between 1-3 and decrease it from the member of int m_starterFlipped tiles.
    As requested - quantity of flipped tiles will be max 14 tiles, minimum 4 tiles.
    This algorithm creates a random game with a random quantity of levels! 
3.  This program uses BFS algorithm to calculate and find the shortest path for the cat to reach the outlines.
    While using BFS algorithm, we randomize the options of the shortest path and choose randomly one of them as
    the current path of the cat to move. 

==============================================================================  

Files list :
Header Files :
Board.h		-> Incharge of everything that happens on the game board.
Button.h 		-> Incharge and initialize the buttons of the game.
Cat.h		-> Initialize the Cat.
Consts.h		-> Contains constant variables of the program.
Controller.h	-> Controls the order of actions.
GameObject.h	-> Incharge and initialize the game objects.
Menu.h		-> Incharge of of the menu.
Resources.h	-> Singletone class. Loads all the needed resources. contains enums.
Tile.h		-> Initialize the tiles.

.cpp Files :
main.cpp             		
Board.cpp 	-> Incharge of everything that happens on the game board.
Button.cpp	-> Incharge and initialize the buttons of the game.
Cat.cpp		-> Initialize the Cat.
Controller.cpp	-> Controls the order of actions.
GameObject.cpp	-> Incharge and initialize the game objects.
Menu.cpp		-> Incharge of of the menu.
Resources.cpp	-> Singletone class. Loads all the needed resources.
Tile.cpp		-> Initialize the tiles.

==============================================================================
Full-Names : Yehonatan Bakshi & Hila Saadon
