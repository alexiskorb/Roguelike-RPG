// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Dungeon.h"
// You may add data members and other member functions to this class.

class Game
{
public:
	Game(int goblinSmellDistance);
	//Constructor
	void play();
	//Plays the game. The user can move the Player through a Dungeon, pickup weapons, and do many other things.
private:
	Dungeon m_dungeon;	//The Dungeon the Player navigates.
};

#endif // GAME_INCLUDED
