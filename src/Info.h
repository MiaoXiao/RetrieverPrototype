#ifndef INFO_H
#define INFO_H

#include "Ability.h"
#include "Item.h"
#include "Globals.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

//max number of ability categories
#define CATEGORYCAP 3
//max number of ability types per category
#define TYPECAP 5

//path for ability info
#define ABILITYPATH std::string("src/abilities/")

//ability rank cap
#define RANKCAP 3

//info about one ability
struct Node
{
	//CONSTRUCTOR: init abiity that this node refers to
	Node(Ability* a):
	ability(a) {}
	
	Ability* ability;
	
	//stores children of this node (future abilities that can be learned)
	std::vector<Node*> children;
};

//Tree of abilities, controls which abilities can be obtained first
struct SkillTree
{
	//holds all abilities
	std::vector <Node> list;
	
	//new abilities the player can learn upon leveling up
	std::vector <Node*> newAbilities;
	//the next abilities that can be ranked up
	std::vector <Node*> rankAbilities;
	
	//learn a new ability
	std::vector<unsigned int> learn_Ability(const unsigned int abilityPoints, std::vector<unsigned int> al)
	{	
		std::vector<unsigned int> abilityList = al;
		
		int choice;
		bool done = false;
		
		//range of abilities to learn and rank up
		int lrange;
		int rrange;
		
		unsigned int pointsLeft = abilityPoints;
		
		while(!done)
		{
			std::cout << pointsLeft << " ability point(s) to spend." << std::endl << std::endl;
			lrange = 0;
			
			std::cout << "Abilities that can be learned: " << std::endl << std::endl;
			if (newAbilities.size() == 0) std::cout << "NONE" << std::endl;
			else
			{
				//display all new abilities that can be learned
				for (unsigned int i = 0; i < newAbilities.size(); ++i)
				{
					std::cout << lrange << ": " << newAbilities[i]->ability->get_Name() << std::endl;
					std::cout << newAbilities[i]->ability->get_Description() << std::endl << std::endl;
					lrange++;
				}
			}
			std::cout << std::endl;
			
			rrange = lrange;
			std::cout << "Abilities that can be improved: " << std::endl << std::endl;
			if (rankAbilities.size() == 0) std::cout << "NONE" << std::endl;
			else
			{
				//display all abilities that can be improved
				for (unsigned int i = 0; i < rankAbilities.size(); ++i)
				{
					std::cout << rrange << ": " << rankAbilities[i]->ability->get_Name() << std::endl;
					std::cout << rankAbilities[i]->ability->get_Description() << std::endl << std::endl;
					rrange++;
				}
			}
			
			std::cout << std::endl << "Choose any ability to learn or improve." << std::endl;
			std::cin >> choice;
			
			//check input
			if (choice < 0 || choice > rrange)
			{
				std::cout << std::endl << "Not a valid ability to learn or improve, try again." << std::endl << std::endl;
			}
			else
			{
				//learn ability
				if (choice < lrange)
				{	
					std::cout << "Learned " << newAbilities[choice]->ability->get_Name() << "!" << std::endl;
					abilityList.push_back(newAbilities[choice]->ability->get_Id());
					newAbilities.erase(find(newAbilities.begin(), newAbilities.end(), newAbilities[choice]));
					rankAbilities.push_back(&list[choice]);
				}
				else //improve ability
				{
					std::cout << "Improved " << newAbilities[choice]->ability->get_Name() << "!" << std::endl;
					list[choice - lrange].ability->change_Rank(1);
					//if ability is now at max rank, remove ability from list of possible abilities to rank up
					if (list[choice - lrange].ability->get_Rank() == RANKCAP) rankAbilities.erase(find(rankAbilities.begin(), rankAbilities.end(), rankAbilities[choice - lrange]));
				}
				
				std::cout << std::endl;
				//keep track of how many points are left
				pointsLeft--;
				if (pointsLeft == 0) done = true;
				
			}
		}
		//sort ability list
		std::sort (abilityList.begin(), abilityList.end());
		return abilityList;
	}
	
};

//manages abilities and player skill trees and items
class Info
{
	public:
		//CONSTRUCTOR: set sizes for pool vectors
		Info() 
		{
			load_Abilities();
			load_Trees();
		}
		
		//controls which abilities can be obtained first for each player
		SkillTree p1AbilityTree;
		SkillTree p2AbilityTree;
		
		//get all abilities for a player
		std::vector<Ability> get_PlayerAbilityPool() const;
		//get all items that can be obtained or dropped
		std::vector<Item> get_ItemPool() const;
		
	private:
		//name of each file to read
		std::string filename;
		
		//player pool
		std::vector<Ability> playerAbilityPool;
		//item pool
		std::vector<Item> itemPool;
		
		//loads all possible abilities
		void load_Abilities();
		//assign ability to correct character pool
		void assign_ToAbilityPool(Ability a, std::vector<std::string> usage, unsigned int category, unsigned int type);
		//fill player trees
		void load_Trees();
		
		//loads all possible items
		void load_Items();
};
#endif
