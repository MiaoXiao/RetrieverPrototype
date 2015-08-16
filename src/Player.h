#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

#include <string>
#include <fstream>

//The Player is the instance that the game-player controls.
class Player: public Character
{
	public:
		//CONSTRUCTOR: ini#FFFFFFt instance of player and starting funds
		Player():
			digits(0),
			fullParty(false) {}
		
		//CONSTRUCTOR: init instance of playable character and pronoun
		Player(std::string fn):
			digits(0),
			fullParty(false)
		{
			isPlayer = true;
			isAlive = true;
			
			assign_StartInfo(fn);
		}
		
		//get current funds
		int get_Digits() const;
		//set current funds to v
		void set_Digits(const unsigned int v);
		//change current funds by addving v to digits
		void change_Digits(const int v);
		
		//get enemy point score
		int get_Eps() const;
		//set enemy point score to v
		void set_Eps(const unsigned int v);
		//change current eps by addving v to eps
		void change_Eps(const int v);

	private:
		//current funds
		int digits;
		//enemy point score
		int eps;
		//set to true if both party members are active. set to false if only Tylor is active
		bool fullParty;
		
		//assign starting stats and other information for a character
		void assign_StartInfo(std::string filename);
};

#endif
