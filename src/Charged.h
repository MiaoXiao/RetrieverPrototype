#ifndef CHARGED_H
#define CHARGED_H

#include "Ability.h"
#include "Character.h"

//Ability: Charged Swings
class Charged: public Ability
{
	public:
		Charged(std::string n, std::string description, const unsigned int energy, const float swingmodifier, std::vector<std::string> usage_v, const unsigned int turns):
		chargedturns(turns)
		{
			set_Name(name);
			set_Description(description);
			set_EnergyUsage(energy);
			set_SwingModifier(swingmodifier);
			usage = usage;
			
			//set target size
			singletarget = true;
			
			//set category
			category = Attack;
		}
		
		//use an ability
		void use_Ability(Character *attacker, Character *target);
		
	private:
		//number of turns before this attack goes off
		unsigned int chargedturns;

};

#endif
