//actor.cpp
#include "actor.h"
#include "utilities.h"
#include <iostream>
#include "weapon.h"
#include "GameObject.h"
#include <cmath>
using namespace std;

Actor::Actor(char symbol, string name, int row, int col, int maxHitPts,
	int armorPts, int strPts, int dexPts)
	: m_symbol(symbol), m_name(name), m_row(row), m_col(col), m_maxHitPts(maxHitPts),				//Initializes all of the Actor's member variables
	m_armorPts(armorPts), m_strPts(strPts), m_dexPts(dexPts), m_sleepTime(0), m_weapon(nullptr)
{
	m_hitPts = m_maxHitPts;	
}

Actor::~Actor()
{
	delete m_weapon;
}

string Actor::attack(Actor* target)
{
	string msg = "and misses.\n";

	//Determines whether the attacker hits the target
	int attackerPts = getDexPts() + (getWeapon())->getDexBonus();
	int defenderPts = target->getDexPts() + target->getArmorPts();
	if (randInt(attackerPts) >= randInt(defenderPts)){
		msg = "and hits.\n";		//Sets msg if it hits
	}

	//If the target is hit, the target's hit points go down
	if (msg == "and hits.\n")
	{
		int damagePts = randInt(getStrPts() + (getWeapon())->getDamage());
		target->setHitPts(target->getHitPts() - damagePts);
	}	

	//If the attacker uses a magic fang of sleep, there is a chance to put the target to sleep
	if ((getWeapon())->getName() == "magic fang of sleep" && msg == "and hits.\n")
	{
		//Sleep happens 20% of the time
		if (trueWithProbability(0.2)){
			int x = randInt(5) + 2;
			int y = target->getSleepTime();
			//sleepTime is set to the maximum of the old sleepTime and the new random value
			int sleep = x > y ? x : y;
			target->setSleepTime(sleep);
			//msg is modified to indicate the target has been put to sleep
			msg = "and hits, putting " + target->getName() + " to sleep.\n";
		}
	}
	//If the target has 0 hits points, it is dead and the msg it updated
	if (target->getHitPts() <= 0){
		msg = "dealing a final blow.\n";
	}
	return msg;
}

string Actor::move(const char grid[][70], list<Actor*> monsters, Actor* player)
{
	string msg = "";
	//Player's location
	int pRow = player->getRow();
	int pCol = player->getCol();
	//If the Actor is adjacent to the player
	if ((abs(pRow - getRow()) == 1 && pCol == getCol()) || (pRow == getRow() && abs(pCol - getCol()) == 1))
	{
		//...the Actor will attack the player and update the msg string
		string atk = attack(player);
		msg += getName() + " " + getWeapon()->action() + " the Player " + atk;
	}
	return msg;
}

bool Actor::setRow(int row)
{
	if (row < 0 || row > 17){	//row out of bounds
		return false;
	}
	m_row = row;
	return true;
}
bool Actor::setCol(int col)
{
	if (col < 0 || col > 79){	//col out of bounds
		return false;
	}
	m_col = col;
	return true;
}
bool Actor::setHitPts(int pts)
{
	if (pts < 0){			//pts too low
		m_hitPts = 0;
	}
	else if (pts > m_maxHitPts){	//pts too high
		m_hitPts = m_maxHitPts;
	}
	else{					//pts in range
		m_hitPts = pts;
	}	
	return true;
}
bool Actor::setMaxHitPts(int pts)
{
	if (pts < 0){			//pts too low
		m_maxHitPts = 0;
	} 
	else if (pts > 99){		//pts too high
		m_maxHitPts = 99;
	}
	else{					//pts in range
		m_maxHitPts = pts;
	}
	return true;
}
bool Actor::setArmorPts(int pts)
{
	if (pts < 0){			//pts too low
		m_armorPts = 0;
	}
	else if (pts > 99){		//pts too high
		m_armorPts = 99;
	}
	else{					//pts in range
		m_armorPts = pts;
	}
	return true;
}
bool Actor::setStrPts(int pts)
{
	if (pts < 0){			//pts too low
		m_strPts = 0;
	}
	else if (pts > 99){		//pts too high
		m_strPts = 99;
	}
	else{					//pts in range
		m_strPts = pts;
	}
	return true;
}

bool Actor::setDexPts(int pts)
{
	if (pts < 0){			//pts too low
		m_dexPts = 0;
	}
	else if (pts > 99){		//pts too high
		m_dexPts = 99;
	}
	else{					//pts in range
		m_dexPts = pts;
	}
	return true;
}
bool Actor::setSleepTime(int time)
{
	if (time < 0){			//time too low
		m_sleepTime = 0;
	}
	else if (time > 9){		//time too high
		m_sleepTime = 9;
	}
	else{					//time in range
		m_sleepTime = time;
	}
	return true;
}
bool Actor::setWeapon(Weapon* weapon)
{
	m_weapon = weapon;
	return true;
}

Player::Player(int row, int col)
	: Actor('@', "Player", row, col, 20, 2, 2, 2)
{
	//Sets weapon to a short sword
	ShortSword* playerWeapon = new ShortSword();
	//Adds the short sword to the inventory and weaponry
	setWeapon(playerWeapon);
	m_inventory.push_back(playerWeapon);
	playerWeapon->setWeaponSlot(m_weaponry.size());
	m_weaponry.push_back(playerWeapon);
}
string Player::pickupScroll(GameObject* item)
{
	string msg = "";
	//If the inventory is not full, it adds the item to the inventory
	if (m_inventory.size() <= 25){
		m_inventory.push_back(item);
		msg = "You pick up " + item->getName() + "\n";
	}
	//Otherwise it says that the inventory is full
	else{
		msg = "Your knapsack is full; you can't pick that up.\n";
	}
	return msg;
}
string Player::pickupWeapon(Weapon* item)
{
	string msg = "";
	//If the inventory is not full, it adds the weapon to the inventory and weaponry
	if (m_inventory.size() <= 25){
		m_inventory.push_back(item);
		item->setWeaponSlot(m_weaponry.size());
		m_weaponry.push_back(item);
		msg = "You pick up " + item->getName() + "\n";
	}
	//Otherwise, it says that the inventory is full
	else{
		msg = "Your knapsack is full; you can't pick that up.\n";
	}
	return msg;
}
string Player::selectWeapon(char inventorySlot) 
{
	string msg = "";
	int selection = static_cast<int>(inventorySlot);

	//If the inventorySlot is a lowercase letter that refers to an item in the inventory
	if (selection - 65 >= 0 && selection - 65 < m_inventory.size())
	{
		//Wield the item if it is a weapon
		GameObject* item = m_inventory[selection - 65];
		if (item->isWeapon()){
			setWeapon(m_weaponry[item->getWeaponSlot()]);
			msg = "You are wielding " + item->getName() + "\n";
		}
		else{
			msg = "You can't wield " + item->getName() + "\n";
		}
	}

	//If the inventorySlot is an uppercase letter that refers to an item in the inventory
	if (selection - 97 >= 0 && selection - 97 < m_inventory.size())
	{
		//Wield the item if it is a weapon
		GameObject* item = m_inventory[selection - 97];
		if (item->isWeapon()){
			setWeapon(m_weaponry[item->getWeaponSlot()]);
			msg = "You are wielding " + item->getName() + "\n";
		}
		else{
			msg = "You can't wield " + item->getName() + "\n";
		}
	}
	return msg;
}
string Player::readScroll(char inventorySlot)
{
	string msg = "";
	int selection = static_cast<int>(inventorySlot);

	//If the inventorySlot is a lowercase letter that refers to an item in the inventory
	if (selection - 65 >= 0 && selection - 65 < m_inventory.size()){
		//If it is a scroll, read the scroll
		GameObject* item = m_inventory[selection - 65];
		if (item->isScroll()){
			vector<GameObject*>::iterator p = m_inventory.begin();
			for (int count = 0; count < (selection - 65); p++, count++)
			{}
			msg = item->use(this);
			//Erase the scroll from the inventory
			m_inventory.erase(p);
		}
		else{
			msg = "You can't read a " + item->getName() + "\n";
		}
	}

	//If the inventory slot is an uppercase letter that refers to an item in the inventory
	else if (selection - 97 >= 0 && selection - 97 < m_inventory.size())
	{
		//If the item is a scroll, read the scroll
		GameObject* item = m_inventory[selection - 97];
		if (item->isScroll()){
			vector<GameObject*>::iterator p = m_inventory.begin();
			for (int count = 0; count < (selection - 97); p++, count++)
			{}
			msg = item->use(this);
			//Erase the scroll from the inventory
			m_inventory.erase(p);
		}
		else{
			msg = "You can't read a " + item->getName() + "\n";
		}
	}
	return msg;
}
void Player::displayInventory() 
{
	//Clear the screen and display the title
	clearScreen();
	cout << "Inventory:" << endl;
	char count = 'a';
	//For each item in the inventory, list it after the letter representing its location in the inventory
	for (vector<GameObject*>::iterator p = m_inventory.begin(); p != m_inventory.end(); p++)
	{
		cout << " " << count << ". " << (*p)->getName() << endl;
		count++;	
	}
}
Player::~Player()
{
	//Delete all items in the inventory
	for (vector<GameObject*>::iterator p = m_inventory.begin(); p != m_inventory.end(); p++)
	{
		if (*p != getWeapon())
		{
			delete *p;
		}
	}
	//Clear the inventory and weaponry
	m_inventory.clear();
	m_weaponry.clear();
}


Bogeyman::Bogeyman(int row, int col)		//Constructor
	: Actor('B', "the Bogeyman", row, col, randInt(6) + 5, 
	2, randInt(2) + 2, randInt(2) + 2)
{
	setWeapon(new ShortSword());
}
string Bogeyman::move(const char grid[][70], list<Actor*> monsters, Actor* player)
{
	//Attack the Player if the Bogeyman is next to the Player
	string msg = Actor::move(grid, monsters, player);
	//If the Bogeyman did not attack
	if (msg == "")
	{
		int rowDist = player->getRow() - getRow();
		int colDist = player->getCol() - getCol();  
		//If the Bogeyman is within 5 spots of the Player
		if (abs(rowDist) + abs(colDist) <= 5)
		{  
			bool canMoveRow = true;
			bool canMoveCol = true;
			int tempRow = getRow();
			int tempCol = getCol();
			//Set tempRow to a row one spot closer to the Player if it is not in the same row as the Player
			if (abs(rowDist) > 0){
				tempRow += rowDist / abs(rowDist);
			}
			else{
				canMoveRow = false;
			}
			//set tempCol to a column one spot closer to the Player if it is not in the same col as the Player
			if (abs(colDist) > 0){
				tempCol += colDist / abs(colDist);
			}			
			else{
				canMoveCol = false;
			}
			//If there is a wall in the way, indicate that the Bogeyman can't move that direction.
			if (grid[tempRow][getCol()] == '#'){					
				canMoveRow = false;
			}
			if (grid[getRow()][tempCol] == '#')
			{
				canMoveCol = false;
			}
			//If there is a monster in the way, indicate that the Bogeyman can't move that direction
			for (list<Actor*>::iterator p = monsters.begin(); p != monsters.end(); p++)
			{
				if ((*p)->getRow() == tempRow && (*p)->getCol() == getCol())
				{
					canMoveRow = false;
				}
				if ((*p)->getRow() == getRow() && (*p)->getCol() == tempCol)
				{
					canMoveCol = false;
				}
			}
			//If the Bogeyman can move vertically toward the Player, move it closer
			if (canMoveCol){
				setCol(tempCol);
			}	
			//Otherwise, move the Bogeyman horizontally toward the Player if it can
			else if (canMoveRow){
				setRow(tempRow);
			}					
		}
	}
	return msg;
}

Weapon* Bogeyman::dropWeapon()
{
	//Return a pointer to a MagicAxe 10% of the time
	if (trueWithProbability(0.1)){
		Weapon* item = new MagicAxe(getRow(), getCol());
		return item;
	}
	else{
		return nullptr;
	}
}

Snakewoman::Snakewoman(int row, int col)
	: Actor('S', "the Snakewoman", row, col, (randInt(4) + 3), 3, 2, 3)
{
	setWeapon(new MagicFang());
}
string Snakewoman::move(const char grid[][70], list<Actor*> monsters, Actor* player)
{
	//Attack the Player if the Snakewoman is next to the Player
	string msg = Actor::move(grid, monsters, player);
	//If the Snakewoman did not attack
	if (msg == "")
	{
		int rowDist = player->getRow() - getRow();
		int colDist = player->getCol() - getCol();
		//If the Snakewoman is within 3 spots from the Player
		if (abs(rowDist) + abs(colDist) <= 3)
		{
			bool canMoveRow = true;
			bool canMoveCol = true;
			int tempRow = getRow();
			int tempCol = getCol();
			//Set tempRow to a row one spot closer to the Player if the Snakewoman is not in the same row as the Player
			if (abs(rowDist) > 0){
				tempRow += rowDist / abs(rowDist);
			}
			else{
				canMoveRow = false;
			}
			//Set tempCol to a column one spot closer to the Player if the Snakewoman is not in the same col as the Player
			if (abs(colDist) > 0){
				tempCol += colDist / abs(colDist);
			}
			else{
				canMoveCol = false;
			}
			//If there is a wall in the way, indicate that the Snakewoman can't move that direction
			if (grid[tempRow][getCol()] == '#'){
				canMoveRow = false;
			}
			if (grid[getRow()][tempCol] == '#')
			{
				canMoveCol = false;
			}
			//If there is a monster in the way, indicate that the Snakewoman can't move that direction
			for (list<Actor*>::iterator p = monsters.begin(); p != monsters.end(); p++)
			{
				if ((*p)->getRow() == tempRow && (*p)->getCol() == getCol())
				{
					canMoveRow = false;
				}
				if ((*p)->getRow() == getRow() && (*p)->getCol() == tempCol)
				{
					canMoveCol = false;
				}
			}
			//If the Snakewoman can move one column closer to the player, move it closer
			if (canMoveCol){
				setCol(tempCol);
			}
			//Otherwise, if it can move one row closer to the player, move it closer
			else if (canMoveRow){
				setRow(tempRow);
			}
		}
	}
	return msg;
}
Weapon* Snakewoman::dropWeapon()
{
	int rand = randInt(3);
	//Return a pointer to a MagicFang 1/3 of the time
	if (rand == 0){
		Weapon* item = new MagicFang(getRow(), getCol());
		return item;
	}
	else{
		return nullptr;
	}
}

Dragon::Dragon(int row, int col)
	: Actor('D', "the Dragon", row, col, randInt(6) + 20, 4, 4, 4)
{
	setWeapon(new LongSword());
}
string Dragon::move(const char grid[][70], list<Actor*> monsters, Actor* player)
{
	//1/10 of the time, increase the Dragon's hit points by 1 (up to its maximum hit points)
	if (trueWithProbability(0.1))
	{
		setHitPts(getHitPts() + 1);
	}
	//Attack the Player if the Player is next to the Dragon
	return Actor::move(grid, monsters, player);	
}

GameObject* Dragon::dropScroll()
{
	int rand = randInt(5);
	GameObject* item = nullptr;
	//Return a pointer to a random scroll
	switch (rand)
	{
	case 0: 
		item = new ArmorScroll(getRow(), getCol());
		break;
	case 1:
		item = new DexScroll(getRow(), getCol());
		break;
	case 2:
		item = new TeleportScroll(getRow(), getCol());
		break;
	case 3:
		item = new StrScroll(getRow(), getCol());
		break;
	case 4:
		item = new HealthScroll(getRow(), getCol());
		break;
	}
	return item;
}

Goblin::Goblin(int row, int col, int smellDistance)
	: Actor('G', "the Goblin", row, col, randInt(6) + 15, 1, 3, 1), m_smellDistance(smellDistance)
{
	setWeapon(new ShortSword());
}
Weapon* Goblin::dropWeapon()
{
	int rand = randInt(6);
	//1/6 of the time, return a pointer to a MagicFang
	if (rand == 0){
		Weapon* item = new MagicFang(getRow(), getCol());
		return item;
	}
	//1/6 of the time, return a pointer to a MagicAxe
	else if (rand == 1){
		Weapon* item = new MagicAxe(getRow(), getCol());
		return item;
	}
	else{
		return nullptr;
	}
}

string Goblin::move(const char grid[][70], list<Actor*> monsters, Actor* player)
{
	//If the Goblin is adjacent to the Actor, attack the Actor
	string msg = Actor::move(grid, monsters, player);
	//If the Goblin did not attack
	if (msg == "")
	{
		//Create a grid that has '#' character everywhere there is a wall
		//Put a ' ' in the grid everywhere else
		char modGrid[18][70];
		for (int i = 0; i < 18; i++)
		{
			for (int j = 0; j < 70; j++)
			{
				if (grid[i][j] == '#'){
					modGrid[i][j] = '#';
				}
				else{
					modGrid[i][j] = ' ';
				}
			}
		}
		//At the location of every monster, put a '#' in the grid
		for (list<Actor*>::iterator p = monsters.begin(); p != monsters.end(); p++)
		{
			modGrid[(*p)->getRow()][(*p)->getCol()] = '#';
		}
		int steps = -1;
		//Find the direction of the closest path to the player within m_smellDistance
		int dir = search(modGrid, player, getRow(), getCol(), m_smellDistance, steps);
		//Move the goblin in the direction found in the previous step
		switch (dir)
		{
		case 0:		//Move the goblin up
			setRow(getRow() - 1);
			break;
		case 1:		//Move the goblin down
			setRow(getRow() + 1);
			break;
		case 2:		//Move the goblin right
			setCol(getCol() + 1);
			break;
		case 3:		//Move the goblin left
			setCol(getCol() - 1);
			break;
		default:	//Don't move the goblin since there is not path to the player within the goblin's smelling range
			break;
		}
	}
	return msg;
}

int Goblin::search(char modGrid[][70], Actor* player, int row, int col, int smellDist, int& steps)
{
	//If the row and column is the same as that of the Player, set steps as the smellDist and return a value
	if (row == player->getRow()  &&  col == player->getCol()){
		steps = smellDist;
		return 0;
	}
	//Note that a higher "steps" means the Goblin reaches the player faster

	//If the goblin has not reached the player within 15 steps, indicate that it cannot reach the Player
	if (smellDist < 0){
		return -1;
	}	
	int upSteps = -1;
	int downSteps = -1;
	int rightSteps = -1;
	int leftSteps = -1;

	//Indicate that we have visited this location
	modGrid[row][col] = 'V';

	//If the Goblin can move up, set upSteps to the largest step value that it takes the Goblin to move to the Player 
	//when it moves upward first.
	if (modGrid[row - 1][col] == ' '){
		if (search(modGrid, player, row - 1, col, smellDist - 1, steps) != -1){
			upSteps = steps;
		}
	}
	//If the Goblin can move down, set downSteps to the largest step value that it takes the Goblin to move to the Player
	//when it moves downward first.
	if (modGrid[row + 1][col] == ' '){
		if (search(modGrid, player, row + 1, col, smellDist - 1, steps) != -1){
			downSteps = steps;
		}
	}
	//If the Goblin can move right, set rightSteps to the largest step value that it takes the Goblin to move to the Player
	//when it moves right first
	if (modGrid[row][col + 1] == ' '){
		if (search(modGrid, player, row, col + 1, smellDist - 1, steps) != -1){
			rightSteps = steps;
		}
	}
	//If the Goblin can move left, set leftSteps to the largest step value that it takes the Goblin to move to the Player
	//when it moves left first
	if (modGrid[row][col - 1] == ' '){
		if (search(modGrid, player, row, col - 1, smellDist - 1, steps) != -1){
			leftSteps = steps;
		}
	}
	modGrid[row][col] = ' ';
	//If the Goblin can't reach the Player within smellDist, return -1
	if (upSteps == -1 && downSteps == -1 && rightSteps == -1 && leftSteps == -1){
		return -1;
	}
	//If the Goblin can reach the Player the fastest when moving up first, return 0
	else if (upSteps >= downSteps && upSteps >= rightSteps && upSteps >= leftSteps){
		return 0;
	}
	//If the Goblin can reach the Player the fastest when moving down first, return 1
	else if (downSteps >= upSteps && downSteps >= rightSteps && downSteps >= leftSteps){
		return 1;
	}
	//If the Goblin can reach the Player the fastest when moving right first, return 2
	else if (rightSteps >= upSteps && rightSteps >= downSteps && rightSteps >= leftSteps){
		return 2;
	}
	//If the Goblin can reach the Player the fastest when moving left first, return 3
	else if (leftSteps >= upSteps && leftSteps >= downSteps && leftSteps >= upSteps){
		return 3;
	}
	else{
		return -1;
	}
}
	