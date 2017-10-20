#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED

#include <string>
#include <list>
#include <vector>
using namespace std;

class GameObject;
class Weapon;

class Actor
{
public:
	Actor(char symbol, string name, int row, int col, int maxHitPts,		
		int armorPts, int strPts, int dexPts);							
	//Constructor
	virtual ~Actor();							
	//Destructor

	string attack(Actor* target);
	//The function tells the calling Actor to attack the target Actor.
	//It determines whether the attack hits, kills an Actor, and/or puts an Actor to sleep
		//based on the formulas in the Project 3 specs. 
	//It then adjusts the target Actor's hit points and sleep time accordingly. 
	//It returns a string that details the results of the attack. 

	virtual string move(const char grid[][70], list<Actor*> monsters, Actor* player);
	//Preconditions:
		//grid is the grid of the Dungeon the calling Actor is in. It contains information about where the walls are.
		//monsters is a list of pointers to all the monsters in the Dungeon except for the calling Actor
		//player is a pointer to the player in the dungeon
	//Postconditions:
		//If the player is adjacent to the Actor, the Actor attacks the Player.
		//Otherwise, the Actor does nothing.
		//If an attack occurred, the function returns a string detailing the results of the attack.
		//Otherwise, the fucntion returns an empty string.

	//Loot dropped
	virtual GameObject* dropScroll() { return nullptr; }
	//The nullptr indicates that no scroll is dropped.
	virtual Weapon* dropWeapon() { return nullptr; }
	//The nullptr indicates that no weapon is dropped.

	//Mutator Functions
	//Each function returns true if the value is successfully altered. 
	//Otherwise, the function returns false and does not alter the value.

	bool setRow(int row);	
	//Sets row to "row" if 0 <= row < 18
	bool setCol(int col);		
	//Sets column to "col" if 0 <= col < 80
	bool setSleepTime(int time);
	//If time < 0, m_sleepTime is set to 0
	//If 0 <= time <= 9, m_sleepTime is set to time
	//If time > 9, m_sleepTime is set to 9
	bool setWeapon(Weapon* weapon);
	//Sets m_weapon to "weapon"

	//For each of the following functions,
	//If "pts" is below the range of the variable, the variable is set to its minimum value.
	//If "pts" is within the range of the variable, the variable is set to "pts".
	//IF "pts" is above the range of the variable, the variable is set to the maximum value. 

	bool setHitPts(int pts);
	//Range: 0 <= m_hitPts < m_maxHitPts
	bool setMaxHitPts(int pts);
	//Range: 0 <= m_maxHitPts < 99
	bool setArmorPts(int pts);
	//Range: 0 <= m_armorPts < 99
	bool setStrPts(int pts);
	//Range: 0 < m_strPts < 99
	bool setDexPts(int pts);
	//Range: 0 < dexPts < 99	

	//Accessor Functions
	//Each function returns the corresponding value or pointer

	char getSymbol() const { return m_symbol; }
	string getName() const { return m_name; }
	int getRow() const { return m_row; }
	int getCol() const { return m_col; }
	int getHitPts() const { return m_hitPts; }
	int getMaxHitPts() const { return m_maxHitPts; }
	int getArmorPts() const { return m_armorPts; }
	int getStrPts() const { return m_strPts; }
	int getDexPts() const { return m_dexPts; }
	int getSleepTime() const { return m_sleepTime; }
	Weapon* getWeapon() const { return m_weapon; }
private:
	char m_symbol;		//Character displayed when the Actor is shown in a Dungeon
	string m_name;		//Name of the Actor
	int m_row;			//Row in Dungeon grid
	int m_col;			//Column in Dungeon grid
	int m_hitPts;		//Hit points
	int m_maxHitPts;	//Max hit points
	int m_armorPts;		//Armor points
	int m_strPts;		//Strength points
	int m_dexPts;		//Dexterity points
	int m_sleepTime;	//Amount of turns left to sleep
	Weapon* m_weapon;	//Weapon currently equipped
};

class Player : public Actor
{
public:
	Player(int row, int col);
	//Creates a player at a given row and column
	~Player();
	//Destructor

	string selectWeapon(char inventorySlot);
	//If inventorySlot is the letter of a position in the Inventory that contains a weapon,
	//the Player equips the Weapon at position inventorySlot.
	//If a weapon is equipped this way, the function returns a string describing the action.
	//Otherwise, an empty string is returned.

	string readScroll(char inventorySlot);
	//If inventorySlot is the letter of a position in the Inventory that contains a scroll,
	//the scroll at position inventorySlot is read. 
	//After the magical effects of the scroll take place, the scroll is removed from the inventory.
	//If a scroll is read, a string is returned which explains the effects of the scroll.
	//Otherwise, an empty string is returned.

	string pickupScroll(GameObject* item);
	//If the inventory is not full, the item is added to the inventory. 
	//The function returns a string explaining whether the item was picked up or whether the inventory was full.

	string pickupWeapon(Weapon* item);
	//If the inventory is not full, the item is added to the inventory.
	//Additionally, the item is added to the weaponry. The weaponSlot value of item is set to the position of item in the Weaponry.
	//The function returns a string explaining whether the item was picked up or whether the inventory was full.

	void displayInventory();
	//The screen is cleared and the inventory is displayed in the following format:
	//Inventory:
	// a. first_item
	// b. second_item
	// c. third_item
	// ...

private:
	vector<GameObject*> m_inventory;	//Contains pointers to all of the GameObjects in the Player's possession
	vector<Weapon*> m_weaponry;			//Contains pointers to all of the Weapons in the Player's inventory.
										//The weaponSlot values of these Weapons are set to the corresponding position of the Weapon in the weaponry
};

class Bogeyman : public Actor
{
public:
	Bogeyman(int row, int col);			
	//Creates a Bogeyman at row "row" and column "col"
	virtual string move(const char grid[][70], list<Actor*> monsters, Actor* player);
	//Preconditions:
		//grid is the grid of the Dungeon the calling Bogeyman is in. It contains information about where the walls are.
		//monsters is a list of pointers to all the monsters in the Dungeon except for the calling Bogeyman
		//player is a pointer to the player in the dungeon
	//Postconditions:
		//If the Bogeyman is adjacent to the Player, the Bogeyman attacks the Player.
		//Otherwise, if the Bogeyman is five spaces or fewer away from the Player, 
		//it moves closers to the player (as long as it's path is not blocked by a wall or another monster). 
		//Otherwise, the Bogeyman does not move.
		//If an attack occurred, the function returns a string detailing the results of the attack.
		//Otherwise, the fucntion returns an empty string.
	virtual Weapon* dropWeapon();
	//Returns a pointer to a MagicAxe 10% of the time and 
	// a nullptr 90% of the time.
};

class Snakewoman : public Actor
{
public:
	Snakewoman(int row, int col);
	//Creates a Snakewoman at row "row" and column "col"
	virtual string move(const char grid[][70], list<Actor*> monsters, Actor* player);
	//Preconditions:
		//grid is the grid of the Dungeon the calling Snakewoman is in. It contains information about where the walls are.
		//monsters is a list of pointers to all the monsters in the Dungeon except for the calling Snakewoman
		//player is a pointer to the player in the dungeon
	//Postconditions:
		//If the Snakewoman is adjacent to the Player, the Snakewoman attacks the Player.
		//Otherwise, if the Snakewoman is three spaces or fewer away from the Player, 
		//it moves closers to the player (as long as it's path is not blocked by a wall or another monster). 
		//Otherwise, the Snakewoman does not move.
		//If an attack occurred, the function returns a string detailing the results of the attack.
		//Otherwise, the fucntion returns an empty string.
	virtual Weapon* dropWeapon();
	//Returns a pointer to a MagicFang 1/3 of the time and
	// a nullptr 2/3 of the time
};

class Dragon : public Actor
{
public:
	Dragon(int row, int col);
	//Creates a dragon at row "row" and column "col"
	virtual string move(const char grid[][70], list<Actor*> monsters, Actor* player); 
	//Preconditions:
		//grid is the grid of the Dungeon the calling Dragon is in. It contains information about where the walls are.
		//monsters is a list of pointers to all the monsters in the Dungeon except for the calling Dragon
		//player is a pointer to the player in the dungeon
	//Postconditions:
		//The Dragon will gain one hit point (up to its maximum hit points) 10% of the time
		//If the Dragon is adjacent to the Player, the Dragon attacks the Player.
		//Otherwise, the Dragon does nothing.
		//If an attack occurred, the function returns a string detailing the results of the attack.
		//Otherwise, the fucntion returns an empty string.
	virtual GameObject* dropScroll();
	//Returns a pointer to either a TeleportScroll, ArmorScroll, DexScroll, StrScroll, or HealthScroll
};

class Goblin : public Actor
{
public:
	Goblin(int row, int col, int smellDistance);
	//Creates a goblin at a given location with a smelling range equal to smellDistance
	virtual string move(const char grid[][70], list<Actor*> monsters, Actor* player);
	//Preconditions:
		//grid is the grid of the Dungeon the calling Goblin is in. It contains information about where the walls are.
		//monsters is a list of pointers to all the monsters in the Dungeon except for the calling Goblin
		//player is a pointer to the player in the dungeon
	//Postconditions:
		//If the Gobline is adjacent to the Player, the Goblin attacks the Player.
		//Otherwise, if the Goblin can reach the player in m_smellDistance or fewer moves (without going through a wall or monster),
		//it moves one step along the fastest path to the player.
		//If there are two or more "fastest paths," the Goblin can move one step along either of them.
		//Otherwise, the Goblin does not move.
		//If an attack occurred, the function returns a string detailing the results of the attack.
		//Otherwise, the fucntion returns an empty string.

	int search(char modGrid[][70], Actor* player, int row, int col, int smellDist, int& steps);
	//Preconditions:
		//modGrid is a modified grid of the Dungeon. The locations of all walls and monsters are stored as '#'. All other locations are set to ' '. 
		//player is the Player in the Dungeon.
		//row and col are the starting row and column of the Goblin
		//smellDist is the range of the Goblin's smell from location (row, col).
		//steps is initially set to a value < 0
	//Postconditions:
		//modGrid may be changed.
		//If there is a path that takes smellDist or fewer moves to get from (row, col) to the player:
		// steps is m_smellDistance minus the smallest number of moves it takes to get from "row" and "col" to the Player's location.
		// search returns a value representing the direction the Goblin should take to reach the Player's location the fastest.
		//		0 if the Goblin should move up
		//		1 if the Goblin should move down
		//		2 if the Goblin should move right
		//		3 if the Gobin should move left
		//If there is not a path, steps is unchanged and search returns -1.

	virtual Weapon* dropWeapon();
	//Returns a pointer to either a MagicAxe or a MagicFang 1/3 of the time.
private:
	int m_smellDistance;	//Smelling range of Goblin
};


#endif //ACTOR_INCLUDED
