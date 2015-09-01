#include "Ability.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//return single target status
bool Ability::get_SingleTarget() {return singletarget;}

//return if ability is active
bool Ability::get_IsActive() const {return isActive;}

//get rank
unsigned int Ability::get_Rank() const {return rank;}
//set rank
void Ability::set_Rank(const unsigned int v) 
{
	if (v > RANKCAP) rank = RANKCAP;
	rank = v;
}
//change rank, by adding v to rank
void Ability::change_Rank(const int v)
{
	if (v + rank < 1) rank = 1;
	else if (v + rank > RANKCAP) rank = RANKCAP;
	else set_Rank(v + rank);
}

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
