#ifndef PLAYER_H
#define PLAYER_H

#include <string>

//The Player is the instance that the game-player controls.
class Player
{
	public:
		//CONSTRUCTOR: init instance of player and starting funds
		Player():
			digits(0),
			fullParty(false) {}

		//set current funds
		void set_Digits(int v);
		//get current funds
		int get_Digits();
		
		//set enemy point score
		void set_Eps(int v);
		//get enemy point score
		int get_Eps();

	private:
		//current funds
		int digits;
		//enemy point score
		int eps;
		//set to true if both party members are active. set to false if only Tylor is active
		bool fullParty;
		
};

#endif