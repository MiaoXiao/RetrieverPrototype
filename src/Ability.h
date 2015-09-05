#ifndef ABILITY_H
#define ABILITY_H

#include "Character.h"

//abilities that can have various effects on the stats of a player or enemy
class Ability: public Entity
{
	public:		
		//return ability type
		int get_Category() const;
		//return ability type
		int get_Type() const;
		//return ability id
		int get_Id() const;
		
		//return single target status
		bool get_SingleTarget();
		
		//get rank
		unsigned int get_Rank() const;
		//set rank
		void set_Rank(const unsigned int v);
		//change rank, by adding v to rank
		void change_Rank(const int v);
		
		//get energy usage
		int get_EnergyUsage();
		
		//use an ability
		virtual void use_Ability(Character *attacker, std::vector<Character*> target) {return;}
		
	protected:	
		//ability category
		unsigned int category;
		//ability type
		unsigned int type;
		//unique id given to every ability
		unsigned int id;
		
		//rank of ability
		unsigned int rank;
		
		//is this a single target ability or a multi target?
		bool singletarget;

		//set ability category to v
		void set_Category(const unsigned int v);
		//set ability type to v
		void set_Type(const unsigned int v);
		//set ability id to v
		void set_Id(const unsigned int v);
		
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
		//set energy usage
		void set_EnergyUsage(const unsigned int v);
		//change energy usage, by adding v to swing
		void change_EnergyUsage(const int v);
		
};

#endif
