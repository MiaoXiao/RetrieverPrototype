#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Globals.h"

#include <iostream>
#include <algorithm> 
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

//stat points given for each level
#define STATPOINTS 4

//manages basic combat skills
struct Stats
{
	private:
		//PRIMARY STATS: stats you can level up throughout the game
		//life force of an entity
		unsigned int maxhealth = 0;
		int currhealth = 0;
		//energy is how often an entity can use abilities/attacks
		unsigned int maxenergy = 0;
		int currenergy = 0;
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
		
		//HIDDEN STATS: stats that are not shown to the player
		//energy needed/gained for a swing attack
		int swingEnergy = -5;
		//extra energy needed/gained for using an ability (applies to all abilities)
		int abilityEnergy = 0;
		//energy needed/gained for defending
		int defendEnergy = 2;
		//energy needed/gained for using an item
		int itemEnergy = 2;
		//energy needed/gained for waiting
		int waitEnergy = 10;
		//energy needed/gained for running
		int runEnergy = -10;
		
	public:
		
		//allow player to allocate points to stats and abilities
		void levelUpStats(unsigned int points)
		{
			unsigned int statPoints = points * STATPOINTS;
			
			//temp changes
			unsigned int mhChange = 0;
			unsigned int meChange = 0;
			unsigned int reacChange = 0;
			unsigned int sChange = 0;
			unsigned int rChange = 0;
			unsigned int eChange = 0;
			
			std::cout << statPoints << " stat points to allocate." << std::endl;
			
			bool done = false;
			int choice;
			
			while (!done)
			{
				std::cout << "Choose which stats to improve. " << std::endl;
				std::cout << statPoints << " points left." << std::endl;
				
				std::cout << "0: MaxHealth " << get_MaxHealth() + mhChange << std::endl;
				std::cout << "1: MaxEnergy " << get_MaxEnergy() + meChange << std::endl;
				std::cout << "2: Reaction " << get_Reaction() - reacChange << std::endl;
				std::cout << "3: Swing " << get_Swing() + sChange << std::endl;
				std::cout << "4: Resistance " << get_Resistance() + rChange << std::endl;
				std::cout << "5: Evasiveness " << get_Evasiveness() + eChange << std::endl << std::endl;
				
				std::cin >> choice;
				std::cout << std::endl;
				
				if (choice < 0 || choice > 5)
				{
					std::cout << "Not a valid stat, try again." << std::endl;
				}
				else
				{
					statPoints--;
					switch (choice)
					{
						case 0: mhChange++;
							break;
						case 1: meChange++;
							break;
						case 2: reacChange++;
							break;
						case 3: sChange++;
							break;
						case 4: rChange++;
							break;
						case 5: eChange++;
							break;
					}
				}
				
				//check if all points allocated
				if (statPoints == 0)
				{
					std::cout << "Press '0' to confirm changes, or anything else to reallocate points." << std::endl;
					
					std::cout << "0: MaxHealth " << get_MaxHealth() << " -> " << get_MaxHealth() + mhChange << std::endl;
					std::cout << "1: MaxEnergy " << get_MaxEnergy() << " -> " << get_MaxEnergy() + meChange << std::endl;
					std::cout << "2: Reaction " << get_Reaction() << " -> " << get_Reaction() - reacChange << std::endl;
					std::cout << "3: Swing " << get_Swing() << " -> " << get_Swing() + sChange << std::endl;
					std::cout << "4: Resistance " << get_Resistance() << " -> " << get_Resistance() + rChange << std::endl;
					std::cout << "5: Evasiveness " << get_Evasiveness() << " -> " << get_Evasiveness() + eChange << std::endl << std::endl;
					
					std::cin >> choice;
					std::cout << std::endl;
					
					if (choice == 0)
					{
						done = true;
						change_MaxHealth(mhChange);
						change_MaxEnergy(meChange);
						change_Reaction(-reacChange);
						change_Swing(-sChange);
						change_Resistance(rChange);
						change_Evasiveness(eChange);
					}
					else
					{
						mhChange = 0;
						meChange = 0;
						reacChange = 0;
						sChange = 0;
						rChange = 0;
						eChange = 0;
						statPoints = points * STATPOINTS;			
					}
				}
			}
		}
		
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
			if (v + currhealth < 0) currhealth = 0;
			else set_CurrHealth(v + currhealth);
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
		
		//get swingEnergy
		int get_SwingEnergy() const {return swingEnergy;}
		//set swingEnergy
		void set_SwingEnergy(const unsigned int v) {swingEnergy = v;}
		//change swingEnergy, by adding v to swingEnergy
		void change_SwingEnergy(const int v)
		{
			if (v + swingEnergy < 0) swingEnergy = 0;
			else set_SwingEnergy(v + swingEnergy);
		}
		
		//get abilityEnergy
		int get_AbilityEnergy() const {return abilityEnergy;}
		//set abilityEnergy
		void set_AbilityEnergy(const unsigned int v) {abilityEnergy = v;}
		//change abilityEnergy, by adding v to abilityEnergy
		void change_AbilityEnergy(const int v)
		{
			if (v + abilityEnergy < 0) abilityEnergy = 0;
			else set_AbilityEnergy(v + abilityEnergy);
		}
		
		//get defendEnergy
		int get_DefendEnergy() const {return defendEnergy;}
		//set defendEnergy
		void set_DefendEnergy(const unsigned int v) {defendEnergy = v;}
		//change defendEnergy, by adding v to defendEnergy
		void change_DefendEnergy(const int v)
		{
			if (v + defendEnergy < 0) defendEnergy = 0;
			else set_DefendEnergy(v + defendEnergy);
		}
		
		//get itemEnergy
		int get_ItemEnergy() const {return itemEnergy;}
		//set defendEnergy
		void set_ItemEnergy(const unsigned int v) {itemEnergy = v;}
		//change defendEnergy, by adding v to defendEnergy
		void change_ItemEnergy(const int v)
		{
			if (v + itemEnergy < 0) itemEnergy = 0;
			else set_ItemEnergy(v + itemEnergy);
		}
		
		//get waitEnergy
		int get_WaitEnergy() const {return waitEnergy;}
		//set waitEnergy
		void set_WaitEnergy(const unsigned int v) {waitEnergy = v;}
		//change waitEnergy, by adding v to waitEnergy
		void change_WaitEnergy(const int v)
		{
			if (v + waitEnergy < 0) waitEnergy = 0;
			else set_WaitEnergy(v + waitEnergy);
		}
		
		//get runEnergy
		int get_RunEnergy() const {return runEnergy;}
		//set runEnergy
		void set_RunEnergy(const unsigned int v) {runEnergy = v;}
		//change runEnergy, by adding v to runEnergy
		void change_RunEnergy(const int v)
		{
			if (v + runEnergy < 0) runEnergy = 0;
			else set_RunEnergy(v + runEnergy);
		}
		
		//DEBUG: show all stats
		void show_Stats() const
		{
			std::cout << "Max Health: " << maxhealth << std::endl;
			std::cout << "Current Health: " << currhealth << std::endl;
			std::cout << "Max Energy: " << maxenergy << std::endl;
			std::cout << "Current Energy: " << currenergy << std::endl;
			std::cout << "Reaction: " << reaction << std::endl;
			std::cout << "Swing: " << swing << std::endl;
			std::cout << "Resistance: " << resistance << std::endl;
			std::cout << "Evasiveness: " << evasiveness << std::endl;
			//unique stats
			std::cout << "Intelligence: " << intelligence << std::endl;
			std::cout << "Focus: " << focus << std::endl;
			std::cout << "FocusMultiplier: " << focusmultiplier << std::endl;
			std::cout << "ReflectPercentage: " << reflectpercentage << std::endl << std::endl;
			//hidden stats
			
		}
};

//manages abilities of a character
struct Abilities
{
	private:
		//array of abilities that this character has
		std::vector<unsigned int> abilityList;
		
	public:
		//get ability list
		std::vector<unsigned int> get_AbilityList() const {return abilityList;}
		//set ability list to v
		void set_AbilityList(const std::vector<unsigned int> v) {abilityList = v;}
		
		//return number abilities character has
		unsigned int get_Size() const {return abilityList.size();}
};


//manages status effects of a character
struct Status
{
	private:
		//between -10 and 10 inclusive
		int mood = 0;
		
		//set to false if this character is wiped out, destroyed
		bool isAlive = true;
		
		//whether player is charging an attack
		bool isCharging = false;
		
		//set to true if player, set to false if enemy
		bool isPlayer;
		
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
		
	public:
		//get defense
		bool get_Defending() const {return defending;}
		//set defense to v (true or false)
		void set_Defending(const bool v) {defending = v;}

		//get isAlive status
		bool get_IsAlive() const {return isAlive;}
		//set isAlive to v (true or false)
		void set_IsAlive(const bool v) {isAlive = v;}
		
		//get isAlive status
		bool get_IsCharging() const {return isCharging;}
		//set isAlive to v (true or false)
		void set_IsCharging(const bool v) {isCharging = v;}
		
		//get isPlayer status
		bool get_IsPlayer() const {return isPlayer;}
		//set isPlayer to v (true or false)
		void set_IsPlayer(const bool v) {isPlayer = v;}
		
		//after every battle reset most statuses; unless characters are wiped out, then reset all
		void reset_Status()
		{
			defending = false;
			stunned = false;
			silenced = false;
			swingsilenced = false;
			uncertain = false;
			broken = false;
			lethargy = false;
			isCharging = false;
		}
};

//handles message prompts specific to that character
struct Message
{
		private:
		public:
};

//manages leveling
struct Level
{
	private:
		//current combat level
		int level = 0;
		//current amount of exp if player
		//amount of exp awarded upon character death if figment
		int experience = 0;
		
		//experience needed to reach the next level
		int levelRange[50] = {50, 100, 200, 400, 800, 1600, 2400, 4800};
		
	public:
		//get level
		int get_Level() const {return level;}
		//set level to v
		void set_Level(const unsigned int v) {level = v;}
		//change level by adding v to level
		void change_Level(const int v)
		{
			if (v + level < 1) level = 1;
			else set_Level(v + level);
		}
		
		//get experience
		int get_Experience() const {return experience;}
		//set experience to v
		void set_Experience(const unsigned int v) {experience = v;}
		//change experience by adding v to experience
		void change_Experience(const int v)
		{
			if (v + experience < 1) experience = 0;
			else set_Experience(v + experience);
		}
		
		//returns true if leveled up, given exp
		bool checkLevelUp() const
		{
			if (get_Experience() >= levelRange[get_Level()]) return true;
			return false;
		}
};

//Any entity with skills, abilities, and stats
class Character: public Entity
{
	public:	
		//pronoun for prompts
		std::string pronoun;
		
		//id for which player/figment type
		std::string id;
		
		//combat stats
		Stats stats;
		//combat abilities
		Abilities abilities;
		//current status
		Status status;
		//current level
		Level level;
		//messages specific to this character
		Message message;
		
		//get energy change, given an action
		int get_EnergyDifference(const unsigned int action);
		//check if an attack is critical
		bool check_Critical() const;
		//returns true if attack is dodged, based on character evasion stat
		bool check_Evasion() const;
		
		//return this character's calculated damage
		int calculate_Damage(const float swingModifier);
		//calculate swing damage from enemy to this character
		//calculate evasion chance, crit chance, defense, and swing multiplier which is defaulted to 1
		//useEnergy determines if this attack should use energy
		void take_SwingDamage(Character *attacker, const float swingMultiplier, const bool useEnergy);
		//take regular damage
		void take_NormalDamage(const int damage);
		
		//character defend and display prompt
		void defend();
		//apply retaliation damage to this character and reduced damage to the defender, based on defender retaliation
		void take_Retaliation(const int damage, Character *defender);
		
		//character waits and restores energy
		void wait();
		
		//character attempts to run. return success or failure
		bool run();
		
	protected:
		//assign starting stats and other information for a character
		virtual void assign_StartInfo(std::string filename, const unsigned int number) = 0;

};

#endif
