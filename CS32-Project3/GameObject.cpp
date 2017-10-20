//GameObject.cpp

#include "GameObject.h"
#include "actor.h"
#include "utilities.h"
#include <string>
using namespace std;

GameObject::GameObject(char symbol, string name, int row, int col)
	:m_symbol(symbol), m_name(name), m_row(row), m_col(col), m_weaponSlot(-1)
{}
void GameObject::setWeaponSlot(int slotNum)
{
	m_weaponSlot = slotNum;
}
bool GameObject::isWeapon() const
{
	//If the object's name is that of a weapon, return true
	return (getName() == "mace" || getName() == "short sword" || getName() == "long sword"
		|| getName() == "magic axe" || getName() == "magic fang of sleep");
}
bool GameObject::isScroll() const
{
	//If the object's name is that of a scroll, return true
	return (getName() == "a scroll of teleportation" || getName() == "a scroll of improve armor"
		|| getName() == "a scroll of raise strength" || getName() == "a scroll of enhance dexterity"
		|| getName() == "a scroll of enhance health");
}

TeleportScroll::TeleportScroll(int row, int col)
	:GameObject('?', "a scroll of teleportation", row, col)
{}
string TeleportScroll::use(Actor* target)
{
	return "teleport";
}

ArmorScroll::ArmorScroll(int row, int col)
	:GameObject('?', "a scroll of improve armor", row, col)
{}
string ArmorScroll::use(Actor* target)
{
	//Increase the target's hit points by 1-3 points and display a message
	target->setArmorPts(target->getArmorPts() + randInt(3) + 1);
	string msg = "You read " + getName() + ". Your armor glows blue.\n";
	return msg;
}

StrScroll::StrScroll(int row, int col)
	:GameObject('?', "a scroll of raise strength", row, col)
{}
string StrScroll::use(Actor* target)
{ 
	//Increase the target's strength points by 1-3 points and display a message
	target->setStrPts(target->getStrPts() + randInt(3) + 1);
	string msg = "You read " + getName() + ". Your muscles bulge.\n";
	return msg;
}

HealthScroll::HealthScroll(int row, int col)
	:GameObject('?', "a scroll of enhance health", row, col)
{}
string HealthScroll::use(Actor* target)
{
	//Increase the target's maximum hit points by 3-8 points and display a message
	target->setMaxHitPts(target->getMaxHitPts() + randInt(6) + 3);
	string msg = "You read " + getName() + ". You feel your heart beating stronger.\n";
	return msg;
}

DexScroll::DexScroll(int row, int col)
	:GameObject('?', "a scroll of enhance dexterity", row, col)
{}
string DexScroll::use(Actor* target)
{
	//Increase the target's dexterity points by 1 and display a message
	target->setDexPts(target->getDexPts() + 1);
	string msg = "You read " + getName() + ". You feel like less of a klutz.\n";
	return msg;
}

