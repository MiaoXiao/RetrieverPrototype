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
		//CONSTRUCTOR: creates figment based on type, figment id, level, number of perks
		Figment(std::string fn, const unsigned number, const unsigned int l, const unsigned int np):
			id(number),
			numbPerks(np)
		{
			//set player flag to false
			status.set_IsPlayer(false);
				
			//set level
			level.set_Level(l);
			//exp gained is level times 10
			level.set_Experience(l * 10);
			
			//assign starting stats
			assign_StartInfo(fn);
		}

	private:
		//id for this figment type
		unsigned int id;
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
