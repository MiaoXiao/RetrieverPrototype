#ifndef ABILITY_H
#define ABILITY_H

#include "Character.h"

//ability rank cap
#define RANKCAP 3

//abilities that can have various effects on the stats of a player or enemy
class Ability: public Entity
{
	public:
		//return single target status
		bool get_SingleTarget();
		
		//return if ability is active
		bool get_IsActive() const;
		
		//get rank
		unsigned int get_Rank() const;
		//set rank
		void set_Rank(const unsigned int v);
		//change rank, by adding v to rank
		void change_Rank(const int v);
		
		
	protected:
		//category chooser
		enum Category {Attack, Support, Debuff};
		//ability category
		unsigned int category;
		
		//whether this ability is active or not
		bool isActive;
		
		//rank of ability
		unsigned int rank;
		
		//is this a single target ability or a multi target?
		bool singletarget;
		
		//determines which characters can use this ability
		std::vector<std::string> usage;
		
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
		virtual void use_Ability(Character *attacker, Character *target) {return;}
};

#endif
