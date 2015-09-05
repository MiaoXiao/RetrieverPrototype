#include "AbilityManager.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//get all abilities for p1
std::vector<Ability> AbilityManager::get_PlayerAbilityPool() const {return playerAbilityPool;}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//
//loads all possible abilities into ability pools for player and enemies
void AbilityManager::load_Abilities()
{
	//stream
	fstream f;
	//info from stream
	string info;
	
	//name of ability type
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
	
	//numeric value for filename numbers
	vector<string> abilityIds;
	abilityIds.push_back("0");
	abilityIds.push_back("1");
	abilityIds.push_back("2");
	abilityIds.push_back("3");
	abilityIds.push_back("4");
	
	//id of ability, unique to that ability. starts at 0
	unsigned int id = 0;
	
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
			f.open((ABILITYPATH + filename).c_str());
			if (f.is_open())
			{
				//cerr << filename << " being read..." << endl;
				//go through list of information in text file
				while (!f.eof())
				{
					f >> info;
					//cerr << "listname: " << info << endl;
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
					else if (info == "Description:")
					{
						f >> info;
						while (info != "*")
						{
							//cout << info << " " << endl;
							abilityDescription += info + " ";
							f >> info;
						}
						f >> info;
					}
					else
					{
						cerr << "Invalid category: " << info << ", in " << filename << ". Exiting." << endl;
						exit(1);
					}
				}
				
				//TEXT FILE MUST HAVE SPECIFIED USAGE
				if (usage.size() == 0)
				{
					cerr << "Need to specify Usage in " << filename << ". Exiting." << endl;
					exit(1);
				}
				
				//based on ability category, assign ability to correct player
				if (abilityTypes[i] == "charged")
				{
					//create the ability depending on the ability type
					Ability a(abilityName, abilityDescription, Globals::Attack_C, Globals::Charged_T, id, energyRequired, swingModifier, turns);
					assign_ToAbilityPool(a, usage, Globals::Attack_C, Globals::Charged_T);
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
			
			//move to next id
			id++;
		}
	}
}

//assign ability to correct either a player or enemy pool
void AbilityManager::assign_ToAbilityPool(Ability a, vector<string> usage, unsigned int category, unsigned int type)
{
	//assign ability to ability pool for all valid character
	for (unsigned int i = 0; i < usage.size(); ++i)
	{
		if (usage[i] == "Player")
		{
			playerAbilityPool.push_back(a);
		}
		else if (usage[i] == "E0")
		{

		}
		else if (usage[i] == "E1")
		{

		}
		else if (usage[i] == "E2")
		{

		}
		else if (usage[i] == "E3")
		{

		}
		else
		{
			cerr << "Invalid character in usage in file " << filename << ". Exiting." << endl;
			exit(1);
		}
	}

}

//fill player trees
void AbilityManager::load_Trees()
{	
	vector<string> treeFiles;
	treeFiles.push_back("p1tree");
	treeFiles.push_back("p2tree");
	
	for (unsigned int i = 0; i < treeFiles.size(); ++i)
	{
		//cout << "next file" << endl;
		//stream for players
		fstream f;	
		
		//holds info from file
		string info;
		
		//open file based on type
		f.open((ABILITYPATH + treeFiles[i]).c_str());
		
		//check if file can be opened
		if (!f.is_open())
		{
			cerr << "Could not open " << treeFiles[i] << ". Exiting." << endl;
			exit(1);
		}
		else
		{
			while (!f.eof())
			{
				//current ability that we are checking
				unsigned int currentId; 
				//cout << info << endl;
				
				currentId = atoi(info.c_str());
				//cout << "id: " << currentId << endl;
				
				f >> info;
				//asterisk indicates next ability
				while (info != "*") 
				{	
					//first ability that can be learned
					if (info == "S") 
					{
						Node n(&playerAbilityPool[currentId]);
						if (treeFiles[i] == "p1tree") //player 1
						{
							p1AbilityTree.list.push_back(n);
							p1AbilityTree.newAbilities.push_back(&p1AbilityTree.list[currentId]); 
						}
						else if (treeFiles[i] == "p2tree") //player 2
						{
							p2AbilityTree.list.push_back(n);
							p2AbilityTree.newAbilities.push_back(&p2AbilityTree.list[currentId]); 
						}
						else
						{
							cerr << "Could not add starting ability, invalid tree name. Exiting." << endl;
							exit(1);
						}
					}
					f >> info;
					//cout << "end " << info << endl;
					//check any children
				}
			}
		}
		f.close();
	}
}
//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
