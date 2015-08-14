#include "Character.h"
#include "Globals.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//check if an attack is critical
bool Character::check_Critical() const
{
	return Probability::chanceToOccur(stats.get_Focus() * 0.01);
}

//returns true if attack is dodged, based on character evasion stat
bool Character::check_Evasion() const
{
	//cout << "dodge: " << stats.get_Evasiveness() * 0.01 << endl;
	return Probability::chanceToOccur(stats.get_Evasiveness() * 0.01);
}

//inflict swing damage on target. damage is within range of swing
int Character::inflict_Damage()
{
	//cout << "inflict swing" << endl;
	return Probability::generateRandomNumber(-Globals::RANGE, Globals::RANGE) + stats.get_Swing();
}

//take damage from enemy
void Character::take_Damage(const int damage)
{
	stats.set_CurrHealth(stats.get_CurrHealth() - damage);
	//if health is brought below 1, change flag
	if (stats.get_CurrHealth() < 1) { isAlive = false; }
}

//if enemy is defending, apply percentage of damage done back to the attacker.
void Character::take_Retaliation(const int damage, const float enemyreflect)
{
	if (enemyreflect < 0 || enemyreflect > 1)
	{
		cout << "Reflect percentage not between 0 and 1. Exiting." << endl;
		exit(1);
	}
	
	//sets current health
	stats.set_CurrHealth(stats.get_CurrHealth() - (damage * enemyreflect));
}

//inflict ability 
void Character::inflict_Ability()
{
	cout << "inflict ability";
}

//DEBUG: show all stats
void Character::showall_Stats() const
{
	cout << endl << get_Name() << " STATS" << endl;
	cout << "Max Health: " << stats.get_MaxHealth() << endl;
	cout << "Current Health: " << stats.get_CurrHealth() << endl;
	cout << "Max Energy: " << stats.get_MaxEnergy() << endl;
	cout << "Current Energy: " << stats.get_CurrEnergy() << endl;
	cout << "Reaction: " << stats.get_Reaction() << endl;
	cout << "Swing: " << stats.get_Swing() << endl;
	cout << "Resistance: " << stats.get_Resistance() << endl;
	cout << "Evasiveness: " << stats.get_Evasiveness() << endl << endl;
	//FIX ME: does not show intelligence yet
}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//



