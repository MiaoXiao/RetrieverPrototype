#ifndef ABILITY_H
#define ABILITY_H

#include "Character.h"

//FORWARD DECLARATION
class Character;

//Abstract Base Class for various affects on the stats of a character
class Ability: public Entity
{
	public:
		
	protected:
		//determines which character can use the ability
		enum CharacterTag {P1, P2};
		
		//category chooser
		enum Category {Attack, Debuff, Support};
		//ability category
		unsigned int category;
		
		//swing damage modieifer
		int swingmodifier;
		
		//energy consumption
		unsigned int energyusage;
		//get energy usage
		int get_EnergyUsage() const;
		//set energy usage
		void set_EnergyUsage(const unsigned int v);
		//change energy usage, by adding v to swing
		void change_EnergyUsage(const int v);
		
		//use an ability
		virtual void use_Ability(Character *attacker, Character *target) = 0;
};

#endif
