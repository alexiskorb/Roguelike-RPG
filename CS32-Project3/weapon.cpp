//weapon.cpp

#include "weapon.h"

Weapon::Weapon(string name, int row, int col, int dexBonus, int damage)	//Sets the member values of Weapon
	: GameObject(')', name, row, col), m_dexBonus(dexBonus), m_damage(damage)
{}

//Simple constructors and functions
Mace::Mace(int row, int col)
	: Weapon("mace", row, col, 0, 2)
{}
string Mace::action() const 
{
	return "swings mace at";
}

ShortSword::ShortSword(int row, int col)
	: Weapon("short sword", row, col, 0, 2)
{}
string ShortSword::action() const
{
	return "slashes short sword at";
}

LongSword::LongSword(int row, int col)
	: Weapon("long sword", row, col, 2, 4)
{}
string LongSword::action() const
{
	return "swings long sword at";
}

MagicAxe::MagicAxe(int row, int col)
	: Weapon("magic axe", row, col, 5, 5)
{}
string MagicAxe::action() const
{
	return "chops magic axe at";
}

MagicFang::MagicFang(int row, int col)
	: Weapon("magic fang of sleep", row, col, 3, 2)
{}
string MagicFang::action() const
{
	return "strikes magic fangs at";
}

