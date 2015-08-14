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
	unsigned int maxhealth;
	unsigned int currhealth;
	//energy is how often an entity can use abilities/attacks
	unsigned int maxenergy;
	unsigned int currenergy;
	//how quickly the entity can attack. A smaller reaction stat means your character will have their turn faster
	unsigned int reaction;
	//damage
	unsigned int swing;
	//chance to resist harmful abilities
	unsigned int resistance;
	//chance to dodge attacks
	unsigned int evasiveness;
	
	//UNIQUE STATS: stats that cannot be improved by normal means
	//how smart the ai of character is
	unsigned int intelligence;
	//crit chance
	unsigned int focus;
	//focus multiplier
	unsigned int focusmultiplier;
	//reflect percentage. percentage of damage reflected back to an attacker, when this character defends
	float reflectpercentage;
	
	//get max health
	int get_MaxHealth() const {return maxhealth;}
	//set max health
	void set_MaxHealth(const int v) {maxhealth = v;}
	
	//get current health
	int get_CurrHealth() const {return currhealth;}
	//set current health
	void set_CurrHealth(const int v) {currhealth = v;}

	//get max energy
	int get_MaxEnergy() const {return maxenergy;}
	//set max energy
	void set_MaxEnergy(const int v) {maxenergy = v;}

	//get current energy
	int get_CurrEnergy() const {return currenergy;}
	//set current energy
	void set_CurrEnergy(const int v) {currenergy = v;}

	//get reaction
	int get_Reaction() const {return reaction;}
	//set reaction
	void set_Reaction(const int v) {reaction = v;}

	//get swing (damage)
	int get_Swing() const {return swing;}
	//set swing (damage)
	void set_Swing(const int v) {swing = v;}

	//get resistance
	int get_Resistance() const {return resistance;}
	//set resistance
	void set_Resistance(const int v) {resistance = v;}
	
	//get evasiveness
	int get_Evasiveness() const {return evasiveness;}
	//set evasiveness
	void set_Evasiveness(const int v) {evasiveness = v;}
	
	//get intelligence
	int get_Intelligence() const {return intelligence;}
	//set intelligence
	void set_Intelligence(const int v) {intelligence = v;}
	
	//get focus
	int get_Focus() const {return focus;}
	//set focus
	void set_Focus(const int v) {focus = v;}
	
	//get focus multiplier
	int get_FocusMultiplier() const {return focusmultiplier;}
	//set focus multiplier
	void set_FocusMultiplier(const int v) {focusmultiplier = v;}
	
	//get reflect percentage
	float get_ReflectPercentage() const {return reflectpercentage;}
	//set reflect percentage
	void set_ReflectPercentage(const int v) {reflectpercentage = v;}
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
