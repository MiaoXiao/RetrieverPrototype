#ifndef FIGMENT_H
#define FIGMENT_H

#include "Enemy.h"

#include <map>
#include <string>

//Every normal/evolved figment in-game
class Figment: public Character
{
	public:	
		//CONSTRUCTOR: creates normal figment based on type, difficulty
		Figment(int type, int difficulty);
		//CONSTRUCTOR: creates evolved figment based on type, difficulty
		Figment(int type, int difficulty, int numbperks);
		
		//assign starting stats
		void assign_Stats();
		
		//ai management
	private:
		//number of abilities
		int numbAbilities;
		
		//damage multiplier
		float swingX;
		//health multiplier
		float healthX;
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