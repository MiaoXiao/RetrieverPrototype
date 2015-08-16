#ifndef FIGMENT_H
#define FIGMENT_H

#include "Character.h"

#include <iostream>
#include <map>
#include <string>

//every enemy in game
class Figment: public Character
{
	public:	
		//CONSTRUCTOR: creates figment based on type, level, area, number of perks
		Figment(std::string fn, const unsigned int l, const unsigned int a, const unsigned int np):
			area(a),
			numbPerks(np)
		{
			//set player flag to false
			isPlayer = false;
			//character is alive at start
			isAlive = true;
		
			//assign starting stats
			assign_StartInfo(fn);
				
			//set level
			level.set_Level(l);
			//exp gained is level times 10
			level.set_Experience(l * 10);
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
		
		//assign starting stats and other information for a character
		void assign_StartInfo(std::string filename);
};

#endif
