#include "Ability.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//
//get swingmodifier
float Ability::get_SwingModifier() const {return swingmodifier;}

//set swingmodifier
void Ability::set_SwingModifier(const unsigned int v) {swingmodifier = v;}

//change swingmodifier, by adding v to swingmodifier
void Ability::change_SwingModifier(const int v)
{
	if (v + swingmodifier < 0) swingmodifier = 0;
	else set_SwingModifier(v + swingmodifier);
}

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

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
