#include "Player.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//current money set
void Player::set_Digits(const int v) {digits = v;}
//current money get
int Player::get_Digits() const {return digits;}

//set enemy point score
void Player::set_Eps(const int v) {eps = v;}
//get enemy point score
int Player::get_Eps() const {return eps;}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
//assign starting stats to player character
void Player::assign_Stats()
{
	//based on name, assign starting stats
	if (name == "Tylor")
	{
		//main stats
		stats.maxhealth = 50;
		stats.currhealth = stats.maxhealth;
		stats.maxenergy = 25;
		stats.currenergy = stats.maxenergy;
		stats.reaction = 50;
		stats.swing = 15;
		stats.resistance = 15;
		stats.evasiveness = 10;
		//unique stats
		stats.intelligence = 115;
		stats.focus = 5;
		stats.focusmultiplier = 3;
	}
	else if (name == "Liza")
	{
		//main stats
		stats.maxhealth = 40;
		stats.currhealth = stats.maxhealth;
		stats.maxenergy = 25;
		stats.currenergy = stats.maxenergy;
		stats.reaction = 50;
		stats.swing = 20;
		stats.resistance = 5;
		stats.evasiveness = 15;
		//unique stats
		stats.intelligence = 115;
		stats.focus = 5;
		stats.focusmultiplier = 3;
	}
	else
	{
		cerr << "Invalid player name. Exiting." << endl;
		exit(1);
	}
}


