#include "Character.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

//inflict swing damage on target. damage is within range of swing
int Character::inflict_Damage()
{
	//cout << "inflict swing" << endl;
	int range = 3;
	return generateRandomNumber(-range, range) + stats.get_Swing();
}

//take damage from enemy
void Character::take_Damage(const int damage)
{
	stats.set_CurrHealth(stats.get_CurrHealth() - damage);
	cout << get_Name() << " takes " << damage << " damage!" << endl;
}

//inflict ability 
void Character::inflict_Ability()
{
	cout << "inflict ability";
}

//DEBUG: show all stats
void Character::showall_Stats() const
{
	cout << "Max Health: " << stats.get_MaxHealth() << endl;
	cout << "Current Health: " << stats.get_CurrHealth() << endl;
	cout << "Max Energy: " << stats.get_MaxEnergy() << endl;
	cout << "Current Energy: " << stats.get_CurrEnergy() << endl;
	cout << "Haste: " << stats.get_Haste() << endl;
	cout << "Swing: " << stats.get_Swing() << endl;
	cout << "Resistance: " << stats.get_Resistance() << endl;
	cout << "Evasiveness: " << stats.get_Evasiveness() << endl;
	//FIX ME: does not show intelligence yet
}

//HELPER FUNCTION: return random number between lower bound and higher bound exclusive
int Character::generateRandomNumber(const int lb, const int hb) const { return rand() % hb + lb; }




