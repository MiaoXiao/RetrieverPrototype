#include "Figment.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
//assign starting stats based on parameters and enemy type
void Figment::assign_Stats(string filename)
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
	
	//base values for level 1 figments
	int startMh = 25;
	int startMe = 10;
	int startReac = 60;
	int startS = 7;
	int startR = 1;
	int startE = 5;
	
	//FIX ME: levels currently have no effect
	stats.maxhealth = (startMh * healthX);
	stats.currhealth = stats.maxhealth;
	stats.maxenergy = (startMe * energyX);
	stats.currenergy = stats.maxenergy;
	stats.reaction = (startReac * reactionX);
	stats.swing = (startS * swingX);
	stats.resistance = (startR * resistanceX);
	
	if (name == "Tank") stats.evasiveness = 0;
	else stats.evasiveness = startE + (startE * evasivenessX); 
	
	showall_Stats();
}
