#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

//manages basic combat skills
struct Stats
{
	//life force of an entity
	int maxhealth;
	int currhealth;
	
	//energy is how often an entity can use abilities/attacks
	int maxenergy;
	int currenergy;
	
	//how quickly the entity can attack
	int haste;
	//damage
	int swing;
	//chance to resist/negative abilities
	int resistance;
	//chance to dodge attacks
	int evasiveness;
	//how smart the ai of entity is
	int intelligence;
};

//manages abilities of a character
struct Abilities
{
	//stores all attack abilities
	std::vector<std::string> attack;
	//stores all defense abilities
	std::vector<std::string> defense;
	//stores all support abilities
	std::vector<std::string> support;
};

//manages status effects of a character
struct Status
{
	//between -10 and 10 inclusive
	int mood = 0;
	//cannot perform any action
	bool stunned = false;
	//percent damage every turn, does not stack
	bool poison = false;
	//cannot use any abilities
	bool silenced = false;
	//cannot use any swing attacks
	bool swingsilenced = false;
	//crit chance reduced to 0 and removes any crit modifiers
	bool uncertain = false;
	//receive more damage from swing attack
	bool broken = false;
	//evasion chance is reduced by half
	bool lethargy = false;
	
	//after every battle reset most statuses; unless characters are wiped out, then reset all
	void resetStatus()
	{
		bool stunned = false;
		bool silenced = false;
		bool swingsilenced = false;
		bool uncertain = false;
		bool broken = false;
		bool lethargy = false;
	}
};

//Any entity with skills, abilities, and stats
class Character
{
	public:		
		//assign starting stats for a character
		void assign_Stats(int mh, int me, int h, int s, int r, int e, int i);
		
		//get max health
		int get_MaxHealth();
		//set max health
		void set_MaxHealth(int v);
		
		//get current health
		int get_CurrHealth();
		//set current health
		void set_CurrHealth(int v);

		//get max energy
		int get_MaxEnergy();
		//set max energy
		void set_MaxEnergy(int v);
	
		//get current energy
		int get_CurrEnergy();
		//set current energy
		void set_CurrEnergy(int v);

		//get haste
		int get_Haste();
		//set haste
		void set_Haste(int v);

		//get swing (damage)
		int get_Swing();
		//set swing (damage)
		void set_Swing(int v);

		//get resistance
		int get_Resistance();
		//set resistance
		void set_Resistance(int v);
		
		//get evasiveness
		int get_Evasiveness();
		//set evasiveness
		void set_Evasiveness(int v);
		
		//get intelligence
		int get_Intelligence();
		//set intelligence
		void set_Intelligence(int v);
		
	protected:
		//combat stats
		Stats stats;
		//combat abilities
		Abilities abilities;
		//current status
		Status status;
};

#endif
