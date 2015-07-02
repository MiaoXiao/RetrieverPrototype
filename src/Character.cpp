#include "Character.h"

//assign starting stats for a character
void assign_Stats(const int mh, const int me, const int h, const int s, const int r, const int e, const int i)
{
	stats.maxhealth = mh;
	stats.currhealth = mh;
	stats.maxenergy = me;
	stats.currenergy = me;
	stats.haste = h;
	stats.swing = s;
	stats.resistance = r;
	stats.evasiveness = e;
	stats.intelligence = i;
}

//get max health
int Character::get_MaxHealth() {return stats.maxhealth;}
//set max health
void Character::set_MaxHealth(int v) {stats.maxhealth = v;}

//get current health
int Character::get_CurrHealth() {return stats.currhealth;}
//set current health
void Character::set_CurrHealth(int v) {stats.currhealth = v;}

//get max energy
int Character::get_MaxEnergy() {return stats.maxenergy;}
//set max energy
void Character::set_MaxEnergy(int v) {stats.maxenergy = v;}

//get current energy
int Character::get_CurrEnergy() {return stats.currenergy;}
//set current energy
void Character::set_CurrEnergy(int v) {stats.currenergy = v;}

//get haste
int Character::get_Haste() {return stats.haste;}
//set haste
void Character::set_Haste(int v) {stats.haste = v;}

//get swing (damage)
int Character::get_Swing() {return stats.swing;}
//set swing (damage)
void Character::set_Swing(int v) {stats.swing = v;}

//get resistance
int Character::get_Resistance() {return stats.resistance;}
//set resistance
void Character::set_Resistance(int v) {stats.resistance = v;}

//get evasiveness
int Character::get_Evasiveness() {return stats.evasiveness;}
//set evasiveness
void Character::set_Evasiveness(int v) {stats.evasiveness = v;}

//get intelligence
int Character::get_Intelligence() {return stats.intelligence;}
//set intelligence
void Character::set_Intelligence(int v) {stats.intelligence = v;}