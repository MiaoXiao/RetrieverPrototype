#include "Player.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//current money get
int Player::get_Digits() {return digits;}
//current money set to v
void Player::set_Digits(const unsigned int v) {digits = v;}
//change current funds by addving v to digits
void Player::change_Digits(const int v)
{
	if (v + digits < 0) digits = 0;
	else set_Digits(v + digits);
}

//get enemy point score
int Player::get_Eps() const {return eps;}
//set enemy point score to v
void Player::set_Eps(const unsigned int v) {eps = v;}
//change current funds by addving v to digits
void Player::change_Eps(const int v)
{
	if (v + eps < 0) eps = 0;
	else set_Eps(v + eps);
}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//

//assign starting stats and other information for a character
void Player::assign_StartInfo(string filename, const unsigned int number)
{
	fstream f;
	//info from stream
	string info;
	
	//cout << "Opening " << filename << "..." << endl;
	f.open(filename.c_str());
	if (!f.is_open())
	{
		cerr << "File could not be opened. Exiting." << endl;
		exit(1);
	}
	//cout << "File opened." << endl;
	
	//assign id; check second character of file
	id = "p" + filename[1];
	
	//get name of character
	f >> info;
	set_Name(info);
	
	f >> info;
	if (info != "gender")
	{
		cerr << "Must have gender category. Exiting." << endl;
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
		else if (info == "reflectpercentage")  
		{
			f >> info;
			stats.set_ReflectPercentage(atof(info.c_str()));
		}
		else 
		{
			cerr << "Invalid Player stat. Exiting." << endl; 
			exit(1);
		}
		//move onto next stat
		f >> info;
	}
	f.close();
	//showall_Stats();
}


