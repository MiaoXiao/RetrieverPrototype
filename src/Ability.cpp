#include "Ability.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//return ability type
int Ability::get_Category() const {return category;}
//return ability type
int Ability::get_Type() const {return type;}
//return ability id
int Ability::get_Id() const {return id;}

//return single target status
bool Ability::get_SingleTarget() {return singletarget;}

//get rank
unsigned int Ability::get_Rank() const {return rank;}
//set rank
void Ability::set_Rank(const unsigned int v) {rank = v;}
//change rank, by adding v to rank
void Ability::change_Rank(const int v)
{
	if (v + rank < 1) rank = 1;
	else set_Rank(v + rank);
}

//get energy usage
int Ability::get_EnergyUsage() {return energyusage;}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//
//set ability category to v
void Ability::set_Category(const unsigned int v) {category = v;}
//set ability type to v
void Ability::set_Type(const unsigned int v) {type = v;}
//set ability id to v
void Ability::set_Id(const unsigned int v) {id = v;}

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

//set energy usage
void Ability::set_EnergyUsage(const unsigned int v) {energyusage = v;}
//change energy usage, by adding v to swing
void Ability::change_EnergyUsage(const int v)
{
	if (v + energyusage < 0) energyusage = 0;
	else set_EnergyUsage(v + energyusage);
}

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
