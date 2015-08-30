#include "Load.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
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
				cerr << filename << " being read..." << endl;
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
				
				//based on ability category, assign ability to correct player
				if (abilityTypes[i] == "charged")
				{
					//create the ability depending on the ability type
					Charged a(abilityName, abilityDescription, energyRequired, swingModifier, usage, turns);
					assign_ToAbilityPool(a, usage, Attack_C, Charged_T);
				}
				else if (abilityTypes[i] == "pierce")
				{
					
				}
				else if (abilityTypes[i] == "area")
				{
					
				}
				else if (abilityTypes[i] == "rapid")
				{
					
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
}

//assign ability to correct character pool
void Load::assign_ToAbilityPool(Ability a, vector<string> usage, unsigned int category, unsigned int type)
{
	//assign ability to ability pool for all valid character
	for (unsigned int i = 0; i < usage.size(); ++i)
	{
		if (usage[i] == "P1")
		{
			p1AbilityPool[category][type].push_back(a);
		}
		else if (usage[i] == "P2")
		{
			p2AbilityPool[category][type].push_back(a);
		}
		else
		{
			cerr << "Invalid character in usage. Exiting." << endl;
			exit(1);
		}
	}

}

//get all abilities for p1
std::vector< std::vector< std::vector<Ability> > > Load::get_P1AbilityPool() const {return p1AbilityPool;}
//get all abilities for p2
std::vector< std::vector< std::vector<Ability> > > Load::get_P2AbilityPool() const {return p2AbilityPool;}
//get all abilities for e0
std::vector< std::vector< std::vector<Ability> > > Load::get_E0AbilityPool() const {return e0AbilityPool;}
//get all abilities for e1
std::vector< std::vector< std::vector<Ability> > > Load::get_E1AbilityPool() const {return e1AbilityPool;}
//get all abilities for e2
std::vector< std::vector< std::vector<Ability> > > Load::get_E2AbilityPool() const {return e2AbilityPool;}
//get all abilities for e3
std::vector< std::vector< std::vector<Ability> > > Load::get_E3AbilityPool() const {return e3AbilityPool;}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
