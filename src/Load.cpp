#include "Load.h"

using namespace std;

//loads all possible abilities
void Load::load_Abilities()
{
	//stream
	fstream f;
	//info from stream
	string info;
	
	//name of file
	string filename;
	
	//all possible ability types in string form
	vector<string> abilityTypes;
	//attack
	abilityTypes.push_back("charged");
	abilityTypes.push_back("pierce");
	abilityTypes.push_back("area");
	abilityTypes.push_back("rapid");
	//support
	abilityTypes.push_back("statbuff");
	//defense
	abilityTypes.push_back("statdebuff");
	
	//stores id for each ability for a specific type in string form
	//at most 5 abilities per type
	vector<string> abilityIds;
	abilityIds.push_back("0");
	abilityIds.push_back("1");
	abilityIds.push_back("2");
	abilityIds.push_back("3");
	abilityIds.push_back("4");
	
	//category of ability
	unsigned int abilityCategory;
	//energy needed for ability
	unsigned int energyRequired;
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
	
	//check all possible ability type and ability ids
	for (unsigned int i = 0; i < abilityTypes.size(); ++i)
	{
		for (unsigned int j = 0; j < abilityIds.size(); ++j)
		{
			//get filename
			filename = abilityTypes[i] + abilityIds[j];
			
			//open file based on type
			f.open(("src/abilities/" + filename).c_str());
			if (f.is_open())
			{
				//cerr << filename << " being read..." << endl;
				//go through list of information in text file
				while (!f.eof())
				{
					f >> info;
					if (info == "Category:")
					{
						f >> info;
						abilityCategory = atoi(info.c_str());
					}
					else if (info == "Name:")
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
							abilityDescription += info + " ";
						}
					}
					else
					{
						cerr << "Invalid category: " << info << ", in " << filename << ". Exiting." << endl;
						exit(1);
					}
				}
				
				if (usage.size() == 0)
				{
					cerr << "Need to specify Usage in " << filename << ". Exiting." << endl;
					exit(1);
				}
				
				//based on ability category, assign ability to correct type
				if (abilityTypes[i] == "charged")
				{
					//cout << "Description: " << abilityDescription << endl;
					//create the ability depending on the ability type
					Charged a(abilityName, abilityDescription, energyRequired, swingModifier, usage, turns);
					chargedAbilities.push_back(a);
				}
				else
				{
					cerr << "Invalid ability type in " << filename << ". Exiting." << endl;
					exit(1);
				}
			
				f.close();
			}
		}
	}
	
	//based on ability usage, assign abilities in correct character vector
	//charged attack
	for (unsigned int i = 0; i < chargedAbilities.size(); ++i)
	{
		vector<string> temp = chargedAbilities[i].get_Usage();
		for (unsigned int j = 0; j < temp.size(); ++j)
		{
			if (temp[j] == "P1") p1Abilities[abilityCategory][Charged_T].push_back(&chargedAbilities[i]);
			else if (temp[j] == "P2") p2Abilities[abilityCategory][Charged_T].push_back(&chargedAbilities[i]);
		}
	}
	
}

//get all abilities for p1
std::vector< std::vector< std::vector<Ability*> > > Load::get_P1Abilities() const { return p1Abilities;}

//get all abilities for p2
std::vector< std::vector< std::vector<Ability*> > > Load::get_P2Abilities() const { return p2Abilities; }
