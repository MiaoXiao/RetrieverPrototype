#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

#include <string>

//The Player is the instance that the game-player controls.
class Player: public Character
{
	public:
		//CONSTRUCTOR: init instance of player and starting funds
		Player():
			digits(0),
			fullParty(false) {}
		
		//CONSTRUCTOR: init instance of playable character
		Player(std::string n):
			digits(0),
			fullParty(false)
		{
			isPlayer = true;
			set_Name(n);
			assign_Stats();
		}

		//assign starting stats
		void assign_Stats();	
		
		//set current funds
		void set_Digits(const int v);
		//get current funds
		int get_Digits() const;
		
		//set enemy point score
		void set_Eps(const int v);
		//get enemy point score
		int get_Eps() const;

	private:
		//current funds
		int digits;
		//enemy point score
		int eps;
		//set to true if both party members are active. set to false if only Tylor is active
		bool fullParty;
		
};

#endif
