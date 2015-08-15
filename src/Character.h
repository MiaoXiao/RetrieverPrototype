#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Globals.h"

#include <string>
#include <vector>

//manages basic combat skills
struct Stats
{
	//PRIMARY STATS: stats you can level up throughout the game
	//life force of an entity
	unsigned int maxhealth = 0;
	unsigned int currhealth = 0;
	//energy is how often an entity can use abilities/attacks
	unsigned int maxenergy = 0;
	unsigned int currenergy = 0;
	//how quickly the entity can attack. A smaller reaction stat means your character will have their turn faster
	unsigned int reaction = 0;
	//damage
	unsigned int swing = 0;
	//chance to resist harmful abilities
	unsigned int resistance = 0;
	//chance to dodge attacks
	unsigned int evasiveness = 0;
	
	//UNIQUE STATS: stats that cannot be improved by normal means
	//how smart the ai of character is
	unsigned int intelligence = 0;
	//crit chance
	unsigned int focus = 0;
	//focus multiplier
	unsigned int focusmultiplier = 0;
	//reflect percentage. percentage of damage reflected back to an attacker, when this character defends
	float reflectpercentage = 0;
	
	//get max health
	int get_MaxHealth() const {return maxhealth;}
	//set max health to v.
	void set_MaxHealth(const unsigned int v) 
	{
		if (v < currhealth) currhealth = maxhealth;
		else maxhealth = v;
	}
	//change max health, by adding v to max health.
	void change_MaxHealth(const int v)
	{
		if (v + maxhealth < 1) maxhealth = 1;
		else set_MaxHealth(v + maxhealth);
	}
	
	//get current health
	int get_CurrHealth() const {return currhealth;}
	//set current health to v.
	void set_CurrHealth(const unsigned int v) 
	{
		if (v >= maxhealth) currhealth = maxhealth;
		else currhealth = v;
	}
	//change current health, by adding v to curr health
	void change_CurrHealth(const int v)
	{
		set_CurrHealth(v + currhealth);
	}

	//get max energy
	int get_MaxEnergy() const {return maxenergy;}
	//set max energy. if brought below curr energy, match curr energy to max energy
	void set_MaxEnergy(const unsigned int v) 
	{
		if (v < currenergy) currenergy = maxenergy;
		else maxenergy = v;
	}
	//change max energy, by adding v to max energy.
	void change_MaxEnergy(const int v)
	{
		if (v + maxenergy < 1) maxenergy = 1;
		else set_MaxEnergy(v + maxenergy);
	}

	//get current energy
	int get_CurrEnergy() const {return currenergy;}
	//set current energy
	void set_CurrEnergy(const unsigned int v) 
	{
		if (v >= maxenergy) currenergy = maxenergy;
		else currenergy = v;
	}
	//change current energy, by adding v to curr energy
	void change_CurrEnergy(const int v)
	{
		if (v + currenergy < 0) currenergy = 0;
		else set_CurrEnergy(v + currenergy);
	}

	//get reaction
	int get_Reaction() const {return reaction;}
	//set reaction
	void set_Reaction(const unsigned int v) {reaction = v;}
	//change reaction, by adding v to reaction
	void change_Reaction(const int v)
	{
		if (v + reaction < 0) reaction = 0;
		else set_Reaction(reaction + v);
	}
	
	//get swing (damage)
	int get_Swing() const {return swing;}
	//set swing (damage)
	void set_Swing(const unsigned int v) {swing = v;}
	//change swing, by adding v to swing
	void change_Swing(const int v)
	{
		if (v + swing < 0) swing = 0;
		else set_Swing(v + swing);
	}

	//get resistance
	int get_Resistance() const {return resistance;}
	//set resistance
	void set_Resistance(const unsigned int v) {resistance = v;}
	//change resistance, by adding v to resistance
	void change_Resistance(const int v)
	{
		if (v + resistance < 0) resistance = 0;
		else set_Resistance(v + resistance);
	}

	//get evasiveness
	int get_Evasiveness() const {return evasiveness;}
	//set evasiveness
	void set_Evasiveness(const unsigned int v) {evasiveness = v;}
	//change evasiveness, by adding v to evasiveness
	void change_Evasiveness(const int v)
	{
		if (v + evasiveness < 0) evasiveness = 0;
		else set_Evasiveness(v + evasiveness);
	}

	//get intelligence
	int get_Intelligence() const {return intelligence;}
	//set intelligence
	void set_Intelligence(const unsigned int v) {intelligence = v;}
	//change intelligence, by adding v to intelligence
	void change_Intelligence(const int v)
	{
		if (v + intelligence < 0) intelligence = 0;
		else set_Intelligence(v + intelligence);
	}

	//get focus
	int get_Focus() const {return focus;}
	//set focus
	void set_Focus(const unsigned int v) {focus = v;}
	//change focus, by adding v to focus
	void change_Focus(const int v)
	{
		if (v + focus < 0) focus = 0;
		else set_Focus(v + focus);
	}

	//get focus multiplier
	int get_FocusMultiplier() const {return focusmultiplier;}
	//set focus multiplier
	void set_FocusMultiplier(const float v) {focusmultiplier = v;}
	//change focus multiplier, by adding v to focus multiplier
	void change_FocusMultiplier(const float v)
	{
		if (v + focusmultiplier < 0) focusmultiplier = 0;
		else set_FocusMultiplier(v + focusmultiplier);
	}
	
	//get reflect percentage
	float get_ReflectPercentage() const {return reflectpercentage;}
	//set reflect percentage
	void set_ReflectPercentage(const float v) {reflectpercentage = v;}
	//change reflect percentage, by adding v to reflect percentage
	void change_ReflectPercentage(const float v)
	{
		if (v + reflectpercentage < 0) reflectpercentage = 0;
		else set_ReflectPercentage(v + reflectpercentage);
	}
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
	
	//whether unit is defending or not
	bool defending = false;
	
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
		bool defending = false;
		bool stunned = false;
		bool silenced = false;
		bool swingsilenced = false;
		bool uncertain = false;
		bool broken = false;
		bool lethargy = false;
	}
};

//manages leveling
struct Level
{
	//current combat level
	int level = 0;
	//amount of exp gained upon death, or current amount of exp
	int experience = 0;
	
	//get level
	int get_Level() const {return level;}
	//set level
	void set_Level(const int v) {level = v;}

	//get experience
	int get_Experience() const {return experience;}
	//set experience
	void set_Experience(const int v) {experience = v;}

	//returns true if leveled up, given exp
	bool checkLevelUp(int e)
	{
		if (e + experience >= Globals::LEVELRANGE[level]) return true;
		return false;
	}
};

//Any entity with skills, abilities, and stats
class Character: public Entity
{
	public:		
		//set to true if player, set to false if enemy
		bool isPlayer;
		
		//set to false if this character is wiped out, destroyed
		bool isAlive;
		
		//pronoun for prompts
		std::string pronoun;
		
		//combat stats
		Stats stats;
		//combat abilities
		Abilities abilities;
		//current status
		Status status;
		//current level
		Level level;
		
		//check if an attack is critical
		bool check_Critical() const;
		
		//returns true if attack is dodged, based on character evasion stat
		bool check_Evasion() const;
		
		//get energy change, given an action
		int get_EnergyDifference(const unsigned int action);
		
		//inflict damage
		int inflict_Damage();

		//take hostile damage
		void take_Damage(const int damage);
		
		//if enemy is defending, apply percentage of damage done back to the attacker.
		void take_Retaliation(const int damage, const float enemyreflect);
		
		//inflict ability on target
		void inflict_Ability();	
		
		//DEBUG: show all stats currently
		void showall_Stats() const;
		
	protected:
		//assign starting stats for a character
		virtual void assign_Stats() = 0;

};

#endif
