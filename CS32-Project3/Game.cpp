// Game.cpp

#include "Game.h"
#include "Dungeon.h"
#include "utilities.h"
#include <iostream>
using namespace std;

Game::Game(int goblinSmellDistance)
	: m_dungeon(goblinSmellDistance)
{}

void Game::play()
{
	//Display the dungeon
	m_dungeon.display();
	//While the game is not over
	while(!m_dungeon.gameOver()){
		//Have the player take a turn
		string playerMsg = m_dungeon.playerTurn(getCharacter());
		//Have the monsters take a turn
		string monsterMsg = m_dungeon.monsterTurn();
		//Display the dungeon and print out what happened
		m_dungeon.display();
		cout << endl << playerMsg << monsterMsg;
	}
	//If the game is over because the player won or ran out of health
	if (!m_dungeon.quit())
	{
		//Quit the game when the user presses 'q'
		cout << "Press q to exit game." << endl;
		while (getCharacter() != 'q')
			;
	}
}
