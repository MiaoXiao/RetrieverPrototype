#ifndef CHARGED_H
#define CHARGED_H

#include "Ability.h"

//Ability: Charged Swings
class Charged: public Ability
{
	public:
		Charged(std::string n, const unsigned int energy, const unsigned int turns, std::string description):
		turns(turns)
		{
			set_Name(name);
			set_Description(description);
			set_EnergyUsage(energy);
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
