#include "Charged.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//use an ability
void Charged::use_Ability(Character *attacker, Character *target)
{
	active = true;
	cout << attacker->get_Name() << " uses " << get_EnergyUsage() << " and begins charging a swing attack!" << endl;
}

//returns true when this attack goes off
bool Charged::countTurns(Character *attacker)
{
	//only count if this move is currently active
	if (active)
	{
		chargedturns++;
		if (chargedturns + 1 == turns) cout << attacker->get_Name() << "'s charged attack will go off on " << attacker->pronoun << " next turn." << endl;
		else if (chargedturns == turns) active = false;
		
		return true;
	}
	return false;
}
		
//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
