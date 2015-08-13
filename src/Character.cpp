#include "Character.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//make decision in combat
void Character::combatDecision() 
{
	cout << "rand numb: " << generateRandomNumber(0, 40) << endl;
	//cout << "combat decision" << endl;
	if (isPlayer) 
	{
		cout << "player turn" << endl;
	}
	else 
	{
		cout << "figment turn" << endl;
	}
	
}

//HELPER FUNCTION: return random number between lower bound and higher bound
int Character::generateRandomNumber(int lb, int hb)
{
        //seed
        //srand(time(NULL));
        return rand() % hb + lb;
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

//inflict swing damage on target. damage is within range of swing
int Character::inflict_Swing()
{
	cout << "inflict swing" << endl;
	int range = 3;
	return generateRandomNumber(-range, range) + stats.get_Swing();
}

//inflict ability 
void Character::inflict_Ability()
{
	cout << "inflict ability";
}


