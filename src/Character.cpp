#include "Character.h"

#include <iostream>

using namespace std;

//get max health
int Character::get_MaxHealth() const {return stats.maxhealth;}
//set max health
void Character::set_MaxHealth(const int v) {stats.maxhealth = v;}

//get current health
int Character::get_CurrHealth() const {return stats.currhealth;}
//set current health
void Character::set_CurrHealth(const int v) {stats.currhealth = v;}

//get max energy
int Character::get_MaxEnergy() const {return stats.maxenergy;}
//set max energy
void Character::set_MaxEnergy(const int v) {stats.maxenergy = v;}

//get current energy
int Character::get_CurrEnergy() const {return stats.currenergy;}
//set current energy
void Character::set_CurrEnergy(const int v) {stats.currenergy = v;}

//get haste
int Character::get_Haste() const {return stats.haste;}
//set haste
void Character::set_Haste(const int v) {stats.haste = v;}

//get swing (damage)
int Character::get_Swing() const {return stats.swing;}
//set swing (damage)
void Character::set_Swing(const int v) {stats.swing = v;}

//get resistance
int Character::get_Resistance() const {return stats.resistance;}
//set resistance
void Character::set_Resistance(const int v) {stats.resistance = v;}

//get evasiveness
int Character::get_Evasiveness() const {return stats.evasiveness;}
//set evasiveness
void Character::set_Evasiveness(const int v) {stats.evasiveness = v;}

//get intelligence
int Character::get_Intelligence() const {return stats.intelligence;}
//set intelligence
void Character::set_Intelligence(const int v) {stats.intelligence = v;}

//DEBUG: show all stats
void Character::showall_Stats() const
{
	cout << "Max Health: " << stats.maxhealth << endl;
	cout << "Current Health: " << stats.currhealth << endl;
	cout << "Max Energy: " << stats.maxenergy << endl;
	cout << "Current Energy: " << stats.currenergy << endl;
	cout << "Haste: " << stats.haste << endl;
	cout << "Swing: " << stats.swing << endl;
	cout << "Resistance: " << stats.resistance << endl;
	cout << "Evasiveness: " << stats.evasiveness << endl;
	//FIX ME: does not show intelligence yet
}

