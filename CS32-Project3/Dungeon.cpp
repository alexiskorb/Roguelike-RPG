//Dungeon.cpp

#include "Dungeon.h"
#include "utilities.h"
#include <iostream>
#include "actor.h"
#include "GameObject.h"
#include "weapon.h"
#include <list>
#include <string>
using namespace std;

Dungeon::Dungeon(int goblinSmellDistance)	//Constructor
	: m_level(0), m_goblinSmellDistance(goblinSmellDistance)	
{
	m_player = new Player(0, 0);
	m_exit = new Exit;
	generateLevel(m_level);
	m_gameOver = false;
	m_quit = false;
}
Dungeon::~Dungeon()
{ 	
	//Delete the Player and the Exit
	delete m_player;
	delete m_exit;
	//Delete all the monsters
	for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++){
		delete *p; 
	}
	m_monsters.clear();
	//Delete all the scrolls
	for (list<GameObject*>::iterator p = m_scrolls.begin(); p != m_scrolls.end(); p++){
		delete *p;
	}
	m_scrolls.clear();
	//Delete all the weapons
	for (list<Weapon*>::iterator p = m_weapons.begin(); p != m_weapons.end(); p++){
		delete *p;
	}
	m_weapons.clear();
}


string Dungeon::playerTurn(char command)
{
	//10% of the time, increase the player's hit points by 1 (up to its maximum hit points)
	if (trueWithProbability(0.1)){
		m_player->setHitPts(m_player->getHitPts() + 1);
	}
	if (m_player->getSleepTime() > 0){
		m_player->setSleepTime(m_player->getSleepTime() - 1);
		return "";
	}
	//Carry out the command
	switch (command)
	{
	//If the command is an indicator for the player to move
	case ARROW_UP:
	case ARROW_DOWN:
	case ARROW_RIGHT:
	case ARROW_LEFT:
		//Move the player in the given direction
		return movePlayer(command);
		break;
	//Get an object
	case 'g':
		//If there is a golden idol at the player's location, indicate that the player has won
		if (m_player->getRow() == m_exit->m_row && m_player->getCol() == m_exit->m_col && m_exit->m_symbol == '&')
		{
			m_gameOver = true;
			return "You pick up the golden idol\nCongratulations, you won!\n";
		}
		//If there is a scroll at the player's location, add it to the player's inventory and erase it from the Dungeon
		for (list<GameObject*>::iterator p = m_scrolls.begin(); p != m_scrolls.end(); p++){
			if ((*p)->getRow() == m_player->getRow() && (*p)->getCol() == m_player->getCol()){
				string msg = m_player->pickupScroll(*p);
				m_scrolls.erase(p);
				return msg;
			}
		}
		//If there is a weapon at the player's location, add it to the player's inventory (and weaponry) and erase it from the Dungeon
		for (list<Weapon*>::iterator p = m_weapons.begin(); p != m_weapons.end(); p++){
			if ((*p)->getRow() == m_player->getRow() && (*p)->getCol() == m_player->getCol()){
				string msg = m_player->pickupWeapon(*p);				
				m_weapons.erase(p);
				return msg;
			}
		}
		break;
	//Wield a weapon
	case 'w':
		//Display the inventory
		m_player->displayInventory();
		//Wield the weapon if a weapon is chosen from the inventory
		return m_player->selectWeapon(getCharacter());
		break;
	//Read a scroll
	case 'r':
		//Display the inventory
		m_player->displayInventory();
		if (true){
			//Read the scroll if a scroll is chosen from the inventory
			string msg = m_player->readScroll(getCharacter());
			//If the scroll read is a scroll of teleportation, teleport the player
			if (msg == "teleport"){
				int row, col;
				getEmptyLocation(row, col);
				m_player->setRow(row);
				m_player->setCol(col);
				return "You read a scroll of teleportation. You feel your body wrenched in space and time.\n";
			}
			else{
				return msg;
			}
		}
		break;
	//Display the inventory
	case 'i':
		//Have the player display the inventory
		m_player->displayInventory();
		//Return to normal after another key is pressed
		getCharacter();
		break;
	//Move down a level
	case '>':
		//If there is a staircase at the player's location, move down a level and generate a new level
		if (m_player->getRow() == m_exit->m_row && m_player->getCol() == m_exit->m_col && m_exit->m_symbol == '>')
		{
			m_level++;
			generateLevel(m_level);
		}
		break;
	//Quit the game
	case 'q':
		//Indicate that the game is over and has been quit
		m_gameOver = true;
		m_quit = true;
		break;
	//Cheat
	case 'c':
		//Set the player's strength points to 9 and its hit point and max hit points to 50
		m_player->setStrPts(9);
		m_player->setMaxHitPts(50);
		m_player->setHitPts(50);
	//If the character is not a valid command, do nothing
	default:
		break;
	}
	return "";
}
string Dungeon::monsterTurn()
{
	//If the game is over, do nothing
	if (gameOver()){
		return "";
	}
	string msg = "";
	int count = 0;

	//Cycle through all the monsters
	for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++, count++)
	{
		Actor* currentMonster = *p;
		//If the monster is asleep, decrement its sleepTime and have it do nothing
		if (currentMonster->getSleepTime() > 0)
		{
			currentMonster->setSleepTime(currentMonster->getSleepTime() - 1);
		}
		//If the monster is not asleep
		else{
			//Create a list of pointers to all the monsters in the Dungeon except for the current monster
			list<Actor*> otherMonsters = m_monsters;
			list<Actor*>::iterator q = otherMonsters.begin();
			for (int i = 0; i < count; i++)
			{
				q++;
			}
			//Erase the current monster from the list of monsters
			otherMonsters.erase(q);
			//Move the current monster 
			msg += currentMonster->move(m_grid, otherMonsters, m_player);
		}
	}
	//If the player has no hit points, indicate that the game is over
	if (m_player->getHitPts() <= 0){
		m_gameOver = true;
	}
	return msg;
}

string Dungeon::movePlayer(char direction)
{
	int row = m_player->getRow();
	int col = m_player->getCol();
	//Set "row" and "col" as the row and column of where the player should move next
	switch (direction)
	{
	case ARROW_UP:	
		row -= 1;
		break;
	case ARROW_DOWN:
		row += 1;
		break;
	case ARROW_RIGHT:
		col += 1;
		break;
	case ARROW_LEFT:
		col -= 1;
		break;
	}
	//Cycle through all the monsters
	for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
	{
		//If there is a monster at this new location, attack the monster
		if (row == (*p)->getRow() && col == (*p)->getCol()){
			string msg = m_player->attack(*p);
			string name = (*p)->getName();
			//If the attack kills the monster
			if (msg == "dealing a final blow.\n")
			{
				//Check if there are scrolls at the monster's location
				bool canLoot = true;
				for (list<GameObject*>::iterator q = m_scrolls.begin(); q != m_scrolls.end(); q++){
					if ((*p)->getRow() == (*q)->getRow() && (*p)->getCol() == (*q)->getCol()){
						canLoot = false;
					}
				}
				//Check if there are weapons at the monster's location
				for (list<Weapon*>::iterator q = m_weapons.begin(); q != m_weapons.end(); q++){
					if ((*p)->getRow() == (*q)->getRow() && (*p)->getCol() == (*q)->getCol()){
						canLoot = false;
					}
				}
				//Check if there is a staircase or idol at the monster's location
				if ((*p)->getRow() == m_exit->m_row && (*p)->getCol() == m_exit->m_col){
					canLoot = false;
				}
				//Drop a scroll or weapon if there is no item at the monster's location
				if (canLoot)
				{
					GameObject* lootScroll = (*p)->dropScroll();
					if (lootScroll != nullptr){
						m_scrolls.push_back(lootScroll);
					}
					Weapon* lootWeapon = (*p)->dropWeapon();
					if (lootWeapon != nullptr){
						m_weapons.push_back(lootWeapon);
					}
				}
				//Erase the monster from the Dungeon
				m_monsters.erase(p);
			}
			//Record the results of teh attack
			msg = "Player " + m_player->getWeapon()->action() + " " + name + " " + msg;
			return msg;
		}
	}
	//Otherwise, if there isn't a wall in the way, move the player to the new location
	if (m_grid[row][col] != '#'){
		m_player->setRow(row);
		m_player->setCol(col);
	}
	return "";
}

void Dungeon::display() 
{
	//Clear the screen and empty the rooms of Actors and GameObjects
	clearScreen();
	clearRooms();
	//For each weapon, mark its location in the grid with a ')'
	for (list<Weapon*>::iterator p = m_weapons.begin(); p != m_weapons.end(); p++)
	{
		m_grid[(*p)->getRow()][(*p)->getCol()] = ')';
	}
	//For each scroll, mark its location in the grid with a '?'
	for (list<GameObject*>::iterator p = m_scrolls.begin(); p != m_scrolls.end(); p++)
	{
		m_grid[(*p)->getRow()][(*p)->getCol()] = '?';
	}
	//Mark the location of the staircase/idol in the grid with its corresponding symbol
	m_grid[m_exit->m_row][m_exit->m_col] = m_exit->m_symbol;
	//For each monster, mark its location in the grid with its corresponding symbol
	for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
	{
		m_grid[(*p)->getRow()][(*p)->getCol()] = (*p)->getSymbol();
	}
	//Mark the location of the player with an '@'
	m_grid[m_player->getRow()][m_player->getCol()] = '@';

	//Print out the grid 
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 70; j++){
			cout << m_grid[i][j];
		}
		cout << endl;
	}
	//Print out information about the player and dungeon
	cout << "Dungeon Level: " << m_level << ", Hit points: " << m_player->getHitPts() << ", Armor: " << m_player->getArmorPts()
		<< ", Strength: " << m_player->getStrPts() << ", Dexterity: " << m_player->getDexPts() << endl;
}
void Dungeon::clearRooms()
{
	//Set every value in m_grid to ' ' unless it is a wall, staircase, or idol
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 70; j++){
			if (m_grid[i][j] != ' ' && m_grid[i][j] != '#' && m_grid[i][j] != '>' && m_grid[i][j] != '&'){
				m_grid[i][j] = ' ';
			}
		}
	}
}

void Dungeon::getEmptyLocation(int &row, int &col) const
{
	row = col = 0;
	//While the location at (row, col) in the grid is not empty
	while (m_grid[row][col] != ' ')
	{
		//Get a random row and column
		row = randInt(16) + 1;
		col = randInt(68) + 1;
	}
}

void Dungeon::drawRoom(Room r1)
{
	//Set the Dungeon's grid to ' ' for every space the room occupies
	for (int i = r1.m_row; i < (r1.m_row + r1.m_length); i++){
		for (int j = r1.m_col; j < (r1.m_col + r1.m_width); j++){
			m_grid[i][j] = ' ';
		}
	}
}

void Dungeon::addRoom(vector<Room>& rooms)
{
	Room rNext;				//The room to be added
	bool canPlace = false;	//Determines whether a room can be placed without overlapping other rooms
	int count = 0;
	//While the room has not been placed and a placement attempt has not been tried more than 10,000 tiems
	while (!canPlace && count < 10000)
	{
		count++;
		canPlace = true;
		//Set the row and col to a random value in the grid
		rNext.m_row = randInt(13) + 1;
		rNext.m_col = randInt(69) + 1;
		//Set the length to a value between 4 and 6
		rNext.m_length = randInt(3) + 4;
		//Set the width to a value between 8 and 19
		rNext.m_width = randInt(10) + 8;
		//If the room would extend pas the bottom of the grid, don't place it
		if (rNext.m_row + rNext.m_length > 16)
		{
			canPlace = false;
		}
		//If the room would extend past the right side of the grid, don't place it
		if (rNext.m_col + rNext.m_width > 68)
		{
			canPlace = false;
		}
		//If the room overlaps with another room, don't place it
		for (int i = 0; i < rooms.size(); i++)
		{
			Room temp = rooms[i];
			bool overlapsHorizontally = false;
			bool overlapsVertically = false;
			//Check whether the room would overlap vertically with other rooms
			if ((temp.m_row <= rNext.m_row && (temp.m_row + temp.m_length + 1) >= rNext.m_row)
				|| (rNext.m_row <= temp.m_row && (rNext.m_row + rNext.m_length + 1) >= temp.m_row))
			{
				overlapsVertically = true;
			}
			//Check whether the room would overlap horizontally with other rooms
			if ((temp.m_col <= rNext.m_col && (temp.m_col + temp.m_width + 1) >= rNext.m_col)
				|| (rNext.m_col <= temp.m_col && (rNext.m_col + rNext.m_width + 1) >= temp.m_col))
			{
				overlapsHorizontally = true;
			}
			//If it would overlap, don't place the room
			if (overlapsHorizontally && overlapsVertically)
			{
				canPlace = false;
			}
		}
	}

	//If there is at least one room already in the dungeon, draw the corridor
	if (!rooms.empty()){
		Room rPrev = rooms[0];
		//Find the square of the distance between the new room and the first room
		int dist = pow(rPrev.m_col - rNext.m_col, 2) + pow(rPrev.m_row - rNext.m_row, 2);
		//Cycle through all the rooms and find the room that is the shortest distance away from the new room
		for (int i = 0; i < rooms.size(); i++)
		{
			int tempDist = pow(rooms[i].m_col - rNext.m_col, 2) + pow(rooms[i].m_row - rNext.m_row, 2);
			if (tempDist < dist)
			{
				rPrev = rooms[i];
				dist = tempDist;
			}
		}
		//Find the middle column and row of the closest room and of the new room
		int rPrevColMid = rPrev.m_col + rPrev.m_width / 2;
		int rPrevRowMid = rPrev.m_row + rPrev.m_length / 2;
		int rNextColMid = rNext.m_col + rNext.m_width / 2;
		int rNextRowMid = rNext.m_row + rNext.m_length/ 2;
		//Draw a corridor vertically from the middle row and middle column of the old room to the middle row of the new room
		for (int i = rPrevRowMid; i != rNextRowMid;)
		{
			m_grid[i][rPrevColMid] = ' ';
			if (i < rNextRowMid){
				i++;
			}
			else if (i > rNextRowMid){
				i--;
			}
		}
		//From the end of that corridor, draw another corridor horizontally until it reaches the middle column of the new room
		for (int i = rPrevColMid; i != rNextColMid;)
		{
			m_grid[rNextRowMid][i] = ' ';
			if (i < rNextColMid){
				i++;
			}
			else if (i > rNextColMid){
				i--;
			}
		}
	}
	//Add the new room to the rooms array
	rooms.push_back(rNext);
	//Draw the new room
	drawRoom(rNext);
}
void Dungeon::generateLevel(int level)
{
	//Clear out old monsters and items
	m_monsters.clear();
	m_scrolls.clear();
	m_weapons.clear();
	//Reset the grid to all '#'
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 70; j++){
			m_grid[i][j] = '#';
		}
	}
	//Number of rooms in the level
	int numRooms = randInt(3) + 5;
	vector<Room> rooms; 
	//Add in the rest of the rooms
	for (int i = 0; i < numRooms; i++)
	{
		addRoom(rooms);
	}
	int row, col;
	//Place the staircase or idol at an empty location
	getEmptyLocation(row, col);
	m_exit->m_row = row;
	m_exit->m_col = col;
	if (level != 4){		//Place a staircase if the level < 4
		m_exit->m_symbol = '>';
	}
	else{					//Place an idol if the level == 4
		m_exit->m_symbol = '&';
	}
	//Place the player at an empty location
	getEmptyLocation(row, col);
	m_player->setRow(row);
	m_player->setCol(col);
	//Place the monsters at empty locations
	int numMonsters = 2 + randInt(5 * (m_level + 1));
	for (int i = 0; i < numMonsters; i++)
	{
		int row, col;
		getEmptyLocation(row, col);
		//Determine which monsters are placed
		int rand;
		if (m_level < 2){		//If level < 2, only the Goblin and Snakewoman are placed
			rand = randInt(2);
		}
		else if (m_level < 3){	//If level < 3, only the Goblin, Snakewoman, and Bogeyman are placed
			rand = randInt(3);
		}
		else{					//If level >= 4, place any of the monsters
			rand = randInt(4);
		}
		//Add a monster to the dungeon
		switch (rand)
		{
		case 0:
			m_monsters.push_back(new Snakewoman(row, col));
			break;
		case 1:
			m_monsters.push_back(new Goblin(row, col, m_goblinSmellDistance));
			break;
		case 2:
			m_monsters.push_back(new Bogeyman(row, col));
			break;
		case 3:
			m_monsters.push_back(new Dragon(row, col));
			break;
		}
	}
	//Place the items at empty locations
	for (int i = 0; i < randInt(2) + 2; i++)
	{
		int row, col;
		getEmptyLocation(row, col);
		//Add a random weapon or scroll to the Dungeon
		int rand = randInt(7);
		switch (rand)
		{
		case 0:
			m_weapons.push_back(new Mace(row, col));
			break;
		case 1:
			m_weapons.push_back(new ShortSword(row, col));
			break;
		case 2:
			m_weapons.push_back(new LongSword(row, col));
			break;
		case 3:
			m_scrolls.push_back(new ArmorScroll(row, col));
			break;
		case 4:
			m_scrolls.push_back(new StrScroll(row, col));
			break;
		case 5:
			m_scrolls.push_back(new HealthScroll(row, col));
			break;
		case 6:
			m_scrolls.push_back(new DexScroll(row, col));
			break;
		}
	}
}