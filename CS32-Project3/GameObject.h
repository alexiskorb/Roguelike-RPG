#ifndef GAME_OBJECT_INCLUDED
#define GAME_OBJECT_INCLUDED

#include <string>
using namespace std;

class Actor;

class GameObject
{
public:
	GameObject(char symbol, string name, int row, int col);
	//Constructor
	virtual ~GameObject() {}
	//Destructor
	virtual string use(Actor* target) = 0;
	//Will return the result of using the GameObject on the target Actor
	void setWeaponSlot(int slotNum);
	//Sets the weaponSlot to slotNum
	bool isWeapon() const;
	//Returns true if the GameObject is a weapon. Returns false otherwise.
	bool isScroll() const;
	//Returns true if the GameObject is a scroll. Returns false otherwise.

	//Accessor functions
	char getSymbol() const { return m_symbol; }
	string getName() const { return m_name; }
	int getRow() const { return m_row; }
	int getCol() const { return m_col; }
	virtual int getWeaponSlot() const { return m_weaponSlot; }
private:
	char m_symbol;		//Character displayed when the GameObject is displayed in a Dungeon.
	string m_name;		//Name of the GameObject
	int m_row;			//Row in Dungeon grid
	int m_col;			//Column in Dungeon grid
	int m_weaponSlot;	//If the GameObject is a Weapon in the Player's inventory, it indicates where in the Player's weaponry the GameObject is located.
};

class TeleportScroll : public GameObject
{
public:
	TeleportScroll(int row = -1, int col = -1);
	//Constructs a scroll of teleportation at row "row" and column "col"
	virtual string use(Actor* target);
	//Returns "teleport", indicating that the Dungeon should teleport the Player
};

class ArmorScroll : public GameObject
{
public:
	ArmorScroll(int row = -1, int col = -1);
	//Constructs a scroll of improve armor at row "row" and column "col"
	virtual string use(Actor* target);
	//Increases the target's armor by 1-3 points and returns a string detailing the change.
};

class StrScroll : public GameObject
{
public:
	StrScroll(int row = -1, int col = -1);
	//Constructs a scroll or raise strength at row "row" and column "col"
	virtual string use(Actor* target);
	//Increases the target's strength by 1-3 points and returns a string detailing the change
};

class HealthScroll : public GameObject
{
public:
	HealthScroll(int row = -1, int col = -1);
	//Constructs a scroll of enhance health at row "row" and column "col"
	virtual string use(Actor* target);
	//Increases the target's max hit points 3-8 points and returns a string detailing the change
};

class DexScroll : public GameObject
{
public:
	DexScroll(int row = -1, int col = -1);
	//Constructs a scroll of enhance dexterity at row "row" and column "col"
	virtual string use(Actor* target);
	//Increases the target's dexterity by 1 and returns a string detailing the change
};

struct Exit
{
public:
	int m_row;		//Row in Dungeon grid
	int m_col;		//Col in Dungeon grid
	char m_symbol;	//'>' if the Exit is a staircase and '&' if the Exit is a golden idol
};


#endif //GAME_OBJECT_INCLUDED
