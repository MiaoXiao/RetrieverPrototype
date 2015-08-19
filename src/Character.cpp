#include "Character.h"
#include "Globals.h"

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
	if (status.get_Defending()) return 0;
	return Probability::chanceToOccur(stats.get_Evasiveness() * 0.01);
}

//get energy change, given an action
int Character::get_EnergyDifference(const unsigned int action)
{
	switch (action)
	{
		case 0: //swing
			return -5;
		case 1: //ability
			return 0;
		case 2: //defend
			return 2;
		case 3: //item
			return 2;
		case 4: //wait
			return 10;
		case 5: //run
			return -10;
		default:
			cerr << "Not a valid action. Exciting" << endl;
			exit(1);
	}
}

//inflict swing damage on target. damage is within range of swing
int Character::inflict_Damage()
{
	//cout << "inflict swing" << endl;
	return Probability::generateRandomNumber(-Globals::RANGE, Globals::RANGE) + stats.get_Swing();
}

//after calculating evasion, crit, and then defending, possibly take damage
//parameters: target name, evade of target, defense of target, reflect percentage of target, character inflicting damage
void Character::take_Damage(string targetname, const bool evade, const bool defend, float rp, Character *c)
{
	//damage
	int d = 0;
	//EVASION check
	if (evade) 
	{
		//PROMPT
		cout << targetname << " evades the attack!" << endl;
	}
	else
	{
		//DAMAGE check
		d = c->inflict_Damage();
		
		//CRITICAL check
		if (c->check_Critical()) 
		{
			//CALCULATION
			d *= c->stats.get_FocusMultiplier();
			//PROMPT
			cout << c->get_Name() << " lands a critical attack!" << endl;
		}
		
		//DEFENSE check
		if (defend)
		{
			c->take_Retaliation(d, rp);
			
			//damage done back to attacker
			int rd = rp * d;
			//damage done to defender
			d *= (1 - rp);
			
			//PROMPT
			cout << targetname << " defends against the attack, and returns " << rd 
				<< " damage back to " << c->get_Name() << "!" << endl;
		}
		
		//PROMPT
		cout << targetname << " takes " << d << " damage!" << endl;
		stats.change_CurrHealth(-d);
		
		//if currhealth is 0 or below, character is defeated
		if (stats.get_CurrHealth() == 0) status.set_IsAlive(false);
	}
	//showall_Stats();
}

//if enemy is defending, apply percentage of damage done back to the attacker.
void Character::take_Retaliation(const int damage, const float enemyreflect)
{
	if (enemyreflect < 0 || enemyreflect > 1)
	{
		cerr << "Reflect percentage not between 0 and 1. Exiting." << endl;
		exit(1);
	}
	
	//sets current health
	stats.change_CurrHealth(-(damage * enemyreflect));
}

//inflict ability 
void Character::inflict_Ability()
{
	cout << "inflict ability";
}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//



