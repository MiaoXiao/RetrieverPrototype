#include "Figment.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
//assign starting stats and other information for a character
void Figment::assign_StartInfo(string filename, const unsigned int number)
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
	
	//get id by checking second character of filename
	id = "e" + filename[1];
	
	//get name of character
	f >> info;
	//convert int to string
	string id_string;
	switch(number)
	{
		case 0:
			id_string = "(A)";
			break;
		case 1:
			id_string = "(B)";
			break;
		case 2:
			id_string = "(C)";
			break;
		case 3:
			id_string = "(D)";
			break;
		case 4:
			id_string = "(E)";
			break;
		case 5:
			id_string = "(F)";
			break;
		default:
			cerr << "Invalid enemy id. Exiting." << endl;
			exit(1);
	}
	set_Name(info + id_string);
	
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
		cerr << "Not a valid gender. (m, f, i). Exiting." << endl; 
		exit(1);
	}
	
	f >> info;
	//cout << "looking at stat: " << info << endl;
	//keep searching until end of file
	while (!f.eof())
	{
		//cout << info << endl;
		if (info == "healthX")
		{
			f >> info;
			healthX = atof(info.c_str());
		}
		else if (info == "energyX") 
		{
			f >> info;
			energyX = atof(info.c_str());
		}
		else if (info == "swingX")  
		{
			f >> info;
			swingX = atof(info.c_str());
		}
		else if (info == "reactionX") 
		{
			f >> info;
			reactionX = atof(info.c_str());
		}
		else if (info == "resistanceX") 
		{
			f >> info;
			resistanceX = atof(info.c_str());
		}
		else if (info == "evasivenessX") 
		{
			f >> info;
			evasivenessX = atof(info.c_str());
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
			cout << "Invalid Figment stat. Exiting." << endl; 
			exit(1);
		}
		//move onto next stat
		f >> info;
	}
	f.close();
	
	stats.set_MaxHealth(level.get_Level() + (Enemy::STARTMH * healthX));
	stats.set_CurrHealth(stats.get_MaxHealth());
	stats.set_MaxEnergy(level.get_Level() + (Enemy::STARTME * energyX));
	stats.set_CurrEnergy(stats.get_MaxEnergy());
	stats.set_Reaction(level.get_Level() + (Enemy::STARTREAC / reactionX));
	stats.set_Swing(level.get_Level() + (Enemy::STARTS * swingX));
	stats.set_Resistance(level.get_Level() + (Enemy::STARTR * resistanceX));
	stats.set_Evasiveness(level.get_Level() + (Enemy::STARTE * evasivenessX)); 
	
	//showall_Stats();
}
