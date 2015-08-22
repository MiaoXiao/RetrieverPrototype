#include "Ability.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//get energy usage
int Ability::get_EnergyUsage() const {return energyusage;}

//set energy usage
void Ability::set_EnergyUsage(const unsigned int v) {energyusage = v;}

//change energy usage, by adding v to swing
void Ability::change_EnergyUsage(const int v)
{
	if (v + energyusage < 0) energyusage = 0;
	else set_EnergyUsage(v + energyusage);
}


//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
