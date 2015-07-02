#include "Player.h"

#include <iostream>

using namespace std;

//assign starting stats to player character
void Player::assign_Stats()
{
	//based on name, assign starting stats
	if (name == "Tylor")
	{
		stats.maxhealth = 50;
		stats.currhealth = stats.maxhealth;
		stats.maxenergy = 25;
		stats.currenergy = stats.maxenergy;
		stats.haste = 10;
		stats.swing = 15;
		stats.resistance = 15;
		stats.evasiveness = 10;
		stats.intelligence = 115;
	}
	else if (name == "Liza")
	{
		stats.maxhealth = 40;
		stats.currhealth = stats.maxhealth;
		stats.maxenergy = 25;
		stats.currenergy = stats.maxenergy;
		stats.haste = 10;
		stats.swing = 20;
		stats.resistance = 5;
		stats.evasiveness = 15;
		stats.intelligence = 115;
	}
	else
	{
		cerr << "Invalid player name" << endl;
	}
}

//current money set
void Player::set_Digits(const int v) {digits = v;}
//current money get
int Player::get_Digits() const {return digits;}

//set enemy point score
void Player::set_Eps(const int v) {eps = v;}
//get enemy point score
int Player::get_Eps() const {return eps;}
