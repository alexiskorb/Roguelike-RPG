//weapon.h

#ifndef WEAPON_INCLUDED
#define WEAPON_INCLUDED

#include "GameObject.h"

#include <string>
using namespace std;

class Weapon : public GameObject
{
public:
	Weapon(string name, int row, int col, int dexBonus, int damage);
	//Constructor
	virtual ~Weapon() {}
	//Destructor
	virtual string action() const = 0;
	//Will return a string detailing how the weapon is used to attack a target

	//Accessor Functions
	int getDexBonus() const { return m_dexBonus; }
	int getDamage() const { return m_damage; }

	virtual string use(Actor* target) { return ""; }
	//Returns an empty string as the Weapon needs a wielder and a target
private:
	int m_dexBonus;		//Dexterity bonus of the Weapon
	int m_damage;		//Damage the Weapon does
};

class Mace : public Weapon
{
public:
	Mace(int row = -1, int col = -1);
	//Constructs a mace at row "row" and column "col"
	virtual string action() const;
	//Returns a string detailing how the mace is used
};

class ShortSword : public Weapon
{
public:
	ShortSword(int row = -1, int col = -1);
	//Constructs a short sword at row "row" and column "col"
	virtual string action() const;
	//Returns a string detailing how the short sword is used.
};

class LongSword : public Weapon
{
public:
	LongSword(int row = -1, int col = -1);
	//Constructs a long sword at row "row" and column "col"
	virtual string action() const;
	//Returns a string detailing how the long sword is used.
};

class MagicAxe : public Weapon
{
public:
	MagicAxe(int row = -1, int col = -1);
	//Constructs a magic axe at row "row" and column "col"
	virtual string action() const;
	//Returns a string detailing how the magic axe is used.
};

class MagicFang : public Weapon
{
public:
	MagicFang(int row = -1, int col = -1);
	//Constructs a magic fang of sleep at row "row" and column "col"
	virtual string action() const;
	//Returns a string detailing how the magic fang of sleep is used.
};

#endif //WEAPON_INCLUDED