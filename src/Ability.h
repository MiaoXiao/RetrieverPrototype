#ifndef ABILITY_H
#define ABILITY_H

#include "Character.h"

//Abstract Base Class for various affects on the stats of a character
class Ability: public Entity
{
	public:
		//return single target status
		bool get_SingleTarget();
		//return vector of characters which can use this ability
		std::vector<std::string> get_Usage();
		
	protected:
		//category chooser
		enum Category {Attack, Support, Debuff};
		//ability category
		unsigned int category;
		
		//determines which characters can use this ability
		std::vector<std::string> usage;
		
		//is this a single target ability or a multi target?
		bool singletarget;
		
		//swing damage modifier
		float swingmodifier;
		//get swing modifier
		float get_SwingModifier() const;
		//set swing modifier
		void set_SwingModifier(const unsigned int v);
		//change swing modifier, by adding v to swing modifier
		void change_SwingModifier(const int v);
		
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
