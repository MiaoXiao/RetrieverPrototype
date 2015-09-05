#ifndef ABILITY_H
#define ABILITY_H

#include "Character.h"
#include "Globals.h"

struct Charged
{
	//number of turns before this attack goes off
	unsigned int maxcharge;
	//how long character has charged for
	unsigned int currentcharge = 0;
	//use the
	void use(Character *attacker, std::vector<Character*> target, const int energyusage, const float swingmodifier)
	{
		//check if currently charging
		if (currentcharge != 0)
		{
			if(currentcharge == maxcharge)
			{
				attacker->status.set_IsCharging(false);
				
				std::cout << attacker->get_Name() << "releases the charged attack!" << std::endl;
				
				for (unsigned int i = 0; i < target.size(); ++i) target[i]->take_SwingDamage(attacker, swingmodifier, false);
				
				currentcharge = 0;
			}
			else if (currentcharge + 1 == maxcharge) 
			{
				std::cout << attacker->get_Name() << "'s charged attack will go off on " << attacker->pronoun << " next turn." << std::endl;
			}
		}
		else
		{
			attacker->status.set_IsCharging(true);
			
			//begin charging
			currentcharge++;
			std::cout << attacker->get_Name() << " uses " << energyusage << " and begins charging a swing attack!" << std::endl;
		}
	}
};

//abilities that can have various effects on the stats of a player or enemy
class Ability: public Entity
{
	public:
		//CONSTRUCTOR: charged attacks
		Ability(std::string n, std::string description, unsigned int category, unsigned int type, unsigned int id, 
						const unsigned int energy, const float swingmodifier, const unsigned int turns)
		{
			
			//name and description
			set_Name(n);
			set_Description(description);
			
			//ability info
			set_Category(category);
			set_Type(type);
			set_Id(id);
			
			//energy usage and extra swing damage
			set_EnergyUsage(energy);
			set_SwingModifier(swingmodifier);
			
			//set target size
			singletarget = true;

			set_Rank(1);
			
			//ABILITYSPECIFIC
			charged.maxcharge = turns;
		}
		
		//return ability type
		int get_Category() const;
		//return ability type
		int get_Type() const;
		//return ability id
		int get_Id() const;
		
		//get rank
		unsigned int get_Rank() const;
		//set rank
		void set_Rank(const unsigned int v);
		//change rank, by adding v to rank
		void change_Rank(const int v);
		
		//return single target status
		bool get_SingleTarget();
		
		//get energy usage
		int get_EnergyUsage();
		//set energy usage
		void set_EnergyUsage(const unsigned int v);
		//change energy usage, by adding v to swing
		void change_EnergyUsage(const int v);
		
		//use an ability
		void use_Ability(Character *attacker, std::vector<Character*> target);
		
	private:
		
		//ability handlers
		Charged charged;
		
		//ability category, type, id
		unsigned int category;
		unsigned int type;
		unsigned int id;
		
		//rank of ability
		unsigned int rank;
		
		//is this a single target ability or a multi target?
		bool singletarget;
	
		//swing damage modifier
		float swingmodifier;
		
		//energy consumption
		unsigned int energyusage;
		
		//set ability category to v
		void set_Category(const unsigned int v);
		//set ability type to v
		void set_Type(const unsigned int v);
		//set ability id to v
		void set_Id(const unsigned int v);
		
		//get swing modifier
		float get_SwingModifier() const;
		//set swing modifier
		void set_SwingModifier(const unsigned int v);
		//change swing modifier, by adding v to swing modifier
		void change_SwingModifier(const int v);
		
};

#endif
