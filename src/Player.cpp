#include "Player.h"

#include <fstream>
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
void Player::assign_Stats(string filename)
{
	fstream f;
	//info from stream
	string info;
	
	//cout << "Opening " << filename << "..." << endl;
	f.open(filename.c_str());
	if (!f.is_open())
	{
		cout << "File could not be opened. Exiting." << endl;
		exit(1);
	}
	//cout << "File opened." << endl;
	
	//get name of character
	f >> info;
	set_Name(info);
	
	f >> info;
	if (info != "gender")
	{
		cout << "Must have gender category. Exiting" << endl;
		exit(1);
	}
	f >> info;
	//get gender
	if (info == "m") pronoun = "his";
	else if (info == "f") pronoun = "her";
	else if (info == "i") pronoun = "its";
	else 
	{
		cout << "Not a valid gender. (m, f, i). Exiting" << endl; 
		exit(1);
	}
	
	f >> info;
	//cout << "looking at stat: " << info << endl;
	//keep searching until end of file
	while (!f.eof())
	{
		if (info == "maxhealth")
		{
			f >> info;
			stats.set_MaxHealth(atoi(info.c_str()));
		}
		else if (info == "currhealth") 
		{
			f >> info;
			stats.set_CurrHealth(atoi(info.c_str()));
		}
		else if (info == "maxenergy")  
		{
			f >> info;
			stats.set_MaxEnergy(atoi(info.c_str()));
		}
		else if (info == "currenergy") 
		{
			f >> info;
			stats.set_CurrEnergy(atoi(info.c_str()));
		}
		else if (info == "reaction") 
		{
			f >> info;
			stats.set_Reaction(atoi(info.c_str()));
		}
		else if (info == "swing") 
		{
			f >> info;
			stats.set_Swing(atoi(info.c_str()));
		}
		else if (info == "resistance")  
		{
			f >> info;
			stats.set_Resistance(atoi(info.c_str()));
		}
		else if (info == "evasiveness")  
		{
			f >> info;
			stats.set_Evasiveness(atoi(info.c_str()));
		}
		else if (info == "intelligence")  
		{
			f >> info;
			stats.set_Intelligence(atoi(info.c_str()));
		}
		else if (info == "focus")  
		{
			f >> info;
			stats.set_Focus(atoi(info.c_str()));
		}
		else if (info == "focusmultiplier")  
		{
			f >> info;
			stats.set_FocusMultiplier(atoi(info.c_str()));
		}
		else 
		{
			cout << "Invalid stat. Exiting." << endl; 
			exit(1);
		}
		//move onto next stat
		f >> info;
	}
	f.close();
	//showall_Stats();
}


