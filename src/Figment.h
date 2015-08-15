#ifndef FIGMENT_H
#define FIGMENT_H

#include "Character.h"

#include <map>
#include <string>

//every enemy in game
class Figment: public Character
{
	public:	
		//CONSTRUCTOR: creates figment based on type, level, area, number of perks
		Figment(const int type, const unsigned int l, const unsigned int a, const unsigned int np):
			area(a),
			numbPerks(np)
		{
			//set level
			level.level = l;
			//set player flag to false
			isPlayer = false;
			//character is alive at start
			isAlive = true;
			//set name
			set_Name(chooseType(type));
			//assign starting stats
			assign_Stats();
			
			//exp gained is level times 10
			level.experience = l * 10;
			
			//set pronoun
			pronoun = "its";
		}

	private:
		//area value where figment is
		unsigned int area;
		//numb of perks
		unsigned int numbPerks;
		//number of abilities
		unsigned int numbAbilities;

		//health multiplier
		float healthX;
		//energy multiplier
		float energyX;
		//damage multiplier
		float swingX;
		//reaction multiplier
		float reactionX;
		//resistance multiplier
		float resistanceX;
		//Eevasiveness multiplier
		float evasivenessX;
		
		//assign starting stats
		void assign_Stats();
		
		//change attribute based on type, return type name
		std::string chooseType(int t);
};

#endif
