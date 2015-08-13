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
			level(l),
			area(a),
			numbPerks(np)
		{
			//set player flag to false
			isPlayer = false;
			//character is alive at start
			isAlive = true;
			//set name
			set_Name(chooseType(type));
			//assign starting stats
			assign_Stats();
		}

		//assign starting stats
		void assign_Stats();

	private:
		//difficulty of figment
		unsigned int level;
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
		//haste multiplier
		float hasteX;
		//resistance multiplier
		float resistanceX;
		//Eevasiveness multiplier
		float evasivenessX;
		
		//HELPER FUNCTION: change attribute based on type, return type name
		std::string chooseType(int t);
};

#endif
