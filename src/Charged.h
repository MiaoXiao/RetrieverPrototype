#ifndef CHARGED_H
#define CHARGED_H

#include "Ability.h"
#include "Character.h"

//Ability: Charged Swings
class Charged: public Ability
{
	public:
		Charged(std::string n, std::string description, const unsigned int energy, const float swingmodifier, std::vector<std::string> usage_v, const unsigned int turns):
		turns(turns)
		{
			set_Name(name);
			set_Description(description);
			set_EnergyUsage(energy);
			set_SwingModifier(swingmodifier);
			
			usage = usage;
			
			category = Attack;
			
			active = false;
			chargedturns = 0;
		}
		
		//use an ability
		void use_Ability(Character *attacker, Character *target);
		
		//returns true when this attack goes off
		bool countTurns(Character *attacker);
		
	private:
		//whether this ability is currently active or not
		bool active;
		//number of turns before this attack goes off
		unsigned int turns;
		//number of turns charged
		unsigned int chargedturns;

};

#endif
