#include "Figment.h"
#include "Globals.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
//assign starting stats and other information for a character
void Figment::assign_StartInfo(string filename)
{
	fstream f;
	//info from stream
	string info;
	
	//open file based on type
	f.open(filename.c_str());
	if (!f.is_open())
	{
		cout << "File could not be opened. Exiting." << endl;
		exit(1);
	}
	
	//get name of character
	f >> info;
	set_Name(info);
	
	f >> info;
	if (info != "gender")
	{
		cout << "Must have gender category. Exiting." << endl;
		exit(1);
	}
	f >> info;
	//get gender
	if (info == "m") pronoun = "his";
	else if (info == "f") pronoun = "her";
	else if (info == "i") pronoun = "its";
	else 
	{
		cout << "Not a valid gender. (m, f, i). Exiting." << endl; 
		exit(1);
	}
	
	f >> info;
	//cout << "looking at stat: " << info << endl;
	//keep searching until end of file
	while (!f.eof())
	{
		if (info == "healthX")
		{
			f >> info;
			healthX = atoi(info.c_str());
		}
		else if (info == "energyX") 
		{
			f >> info;
			energyX = atoi(info.c_str());
		}
		else if (info == "swingX")  
		{
			f >> info;
			swingX = atoi(info.c_str());
		}
		else if (info == "reactionX") 
		{
			f >> info;
			reactionX = atoi(info.c_str());
		}
		else if (info == "resistanceX") 
		{
			f >> info;
			resistanceX = atoi(info.c_str());
		}
		else if (info == "evasivenessX") 
		{
			f >> info;
			evasivenessX = atoi(info.c_str());
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
	
	//FIX ME: levels currently have no effect
	stats.set_MaxHealth(Enemy::STARTMH * healthX);
	stats.set_CurrHealth(stats.get_MaxHealth());
	stats.set_MaxEnergy(Enemy::STARTME * energyX);
	stats.set_CurrEnergy(stats.get_MaxEnergy());
	stats.set_Reaction(Enemy::STARTREAC * reactionX);
	stats.set_Swing(Enemy::STARTS * swingX);
	stats.set_Resistance(Enemy::STARTR * resistanceX);
	stats.set_Evasiveness(Enemy::STARTE * evasivenessX); 
	
	showall_Stats();
}
