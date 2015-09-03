#include "Charged.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//use an ability
void Charged::use_Ability(Character *attacker, Character *target)
{
	//check if currently charging
	if (currentcharge != 0)
	{
		if(currentcharge == maxcharge)
		{
			attacker->status.set_IsCharging(false);
			
			cout << attacker->get_Name() << "releases the charged attack!";
			target->take_SwingDamage(attacker, get_SwingModifier(), false);
			currentcharge = 0;
		}
		else if (currentcharge + 1 == maxcharge) 
		{
			cout << attacker->get_Name() << "'s charged attack will go off on " << attacker->pronoun << " next turn." << endl;
		}
	}
	else
	{
		attacker->status.set_IsCharging(true);
		
		//begin charging
		currentcharge++;
		cout << attacker->get_Name() << " uses " << get_EnergyUsage() << " and begins charging a swing attack!" << endl;
	}
}
		
//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
