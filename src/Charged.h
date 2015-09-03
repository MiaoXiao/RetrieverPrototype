#ifndef CHARGED_H
#define CHARGED_H

#include "Ability.h"
#include "Character.h"

//Ability: Charged Swings
class Charged: public Ability
{
	public:
		Charged(std::string n, std::string description, unsigned int category, unsigned int type, unsigned int id, 
						const unsigned int energy, const float swingmodifier, const unsigned int turns):
		maxcharge(turns)
		{
			//name and description
			set_Name(n);
			set_Description(description);
			
			//vector positions
			set_Category(category);
			set_Type(type);
			set_Id(id);
			
			set_EnergyUsage(energy);
			set_SwingModifier(swingmodifier);
			
			//set target size
			singletarget = true;
			
			currentcharge = 0;
			set_Rank(1);
		}
		
		//use an ability
		void use_Ability(Character *attacker, Character *target);
		
	private:
		//number of turns before this attack goes off
		unsigned int maxcharge;
		//how long character has charged for
		unsigned int currentcharge;

};

#endif
