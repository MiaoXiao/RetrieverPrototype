#include "Charged.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//use an ability
void Charged::use_Ability(Character *attacker, Character *target)
{
	//check if currently charging
	if (attacker->abilities.get_Charges() != 0)
	{
		attacker->abilities.change_Charges(-1);
		if (attacker->abilities.get_Charges() - 1 == 0) cout << attacker->get_Name() << "'s charged attack will go off on " << attacker->pronoun << " next turn." << endl;
		else if (attacker->abilities.get_Charges() == 0)
		{
			cout << attacker->get_Name() << "releases the charged attack!";
			target->take_SwingDamage(attacker, get_SwingModifier(), false);
		}
	}
	else
	{
		//begin charging
		attacker->abilities.set_Charges(chargedturns);
		cout << attacker->get_Name() << " uses " << get_EnergyUsage() << " and begins charging a swing attack!" << endl;
	}
}
		
//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
