#include "Load.h"

using namespace std;

//loads all possible abilities
vector<Ability*> load_Abilities()
{
	//stream
	fstream f;
	//info from stream
	string info;
	
	//name of file
	string filename = "charged0";
	
	//type of ability
	string abilityType;
	//energy needed for ability
	int energyRequired;
	//name of ability
	string abilityName;
	//extra damage that ability can do, based off swing damage
	float swingModifier;
	//description of ability
	string abilityDescription;
	//which character can use the ability
	vector<string> usage;
	
	//turns needed
	int turns;
	
	//ability id
	int aID = 0;
	//number of abilities
	int numbAbilities = 1;
	
	while (aID < numbAbilities)
	{
		//open file based on type
		f.open(filename.c_str());
		if (!f.is_open())
		{
			cout << "File could not be opened. Exiting." << endl;
			exit(1);
		}
		
		while (!f.eof())
		{
			f >> info;
			if (info == "Name:")
			{
				f >> info;
				abilityName = info;
			}
			else if (info == "Energy:")
			{
				f >> info;
				energyRequired = atoi(info.c_str());
			}
			else if (info == "Turns:")
			{
				f >> info;
				turns = atoi(info.c_str());
			}
			else if (info == "SwingModifier:")
			{
				f >> info;
				swingModifier = atof(info.c_str());
			}
			else if (info == "Usage:")
			{
				f >> info;
				do
				{
					usage.push_back(info);
					f >> info;
				} while(info != "done");
			}
			else if (info == "Description:") //description should be the last field in the text file
			{
				while (f >> info)
				{
					abilityDescription += info;
				}
			}
			else
			{
				cerr << "Invalid category for ability. Exiting." << endl;
				exit(1);
			}
		}
		
		Charged a(abilityName, abilityDescription, energyRequired, swingModifier, turns);
		aID++;
	}
	
	f.close();
}
