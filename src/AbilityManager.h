#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include "AbilityManager.h"
#include "Charged.h"

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
	std::vector<std::vector<std::vector<unsigned int> > > learn_Ability(const unsigned int abilityPoints, std::vector<std::vector<std::vector<unsigned int> > > al)
	{
		//copy vector
		std::vector<std::vector<std::vector<unsigned int> > > abilityList = al;
		
		//if vector is empty, init vector
		if (abilityList.size() == 0)
		{
			std::vector< std::vector<unsigned int> > c;
			std::vector<unsigned int> t;
			
			//init category vectors
			for (unsigned int i = 0; i < CATEGORYCAP; ++i)
			{
				abilityList.push_back(c);
				//init type vectors
				for (unsigned int j = 0; j < TYPECAP; ++j)
				{
					abilityList[i].push_back(t);
				}
			}
		}
		
		int choice;
		bool done = false;
		
		//range of abilities to learn and rank up
		int lrange;
		int rrange;
		
		unsigned int pointsLeft = abilityPoints;
		
		while(!done)
		{
			std::cout << pointsLeft << " ability point(s) to spend." << std::endl;
			lrange = 0;
			
			std::cout << "Abilities that can be learned: " << std::endl;
			if (newAbilities.size() == 0) std::cout << "No new abilities to learn." << std::endl;
			else
			{
				//display all new abilities that can be learned
				for (unsigned int i = 0; i < newAbilities.size(); ++i)
				{
					std::cout << lrange << ": " << newAbilities[i]->ability->get_Name() << std::endl;
					std::cout << newAbilities[i]->ability->get_Description() << std::endl;
					lrange++;
				}
			}
			std::cout << std::endl;
			
			rrange = lrange;
			std::cout << "Abilities that can be improved: " << std::endl;
			if (rankAbilities.size() == 0) std::cout << "No abilities to improve." << std::endl;
			else
			{
				//display all abilities that can be improved
				for (unsigned int i = 0; i < rankAbilities.size(); ++i)
				{
					std::cout << rrange << ": " << rankAbilities[i]->ability->get_Name() << std::endl;
					std::cout << rankAbilities[i]->ability->get_Description() << std::endl;
					rrange++;
				}
			}
			
			std::cout << std::endl << "Choose any ability to learn or improve." << std::endl;
			std::cin >> choice;
			
			//check input
			if (choice < 0 || choice > rrange)
			{
				std::cout << "Not a valid ability to learn or improve, try again." << std::endl;
			}
			else
			{
				//track category, type, and id
				unsigned int c = list[choice].ability->get_Category();				
				unsigned int t = list[choice].ability->get_Type();			
				unsigned int i = list[choice].ability->get_Id();
				
				//learn ability
				if (choice < lrange)
				{	
					std::cout << "Learned " << newAbilities[choice]->ability->get_Name() << "!" << std::endl;
					abilityList[c][t].push_back(i);
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
				
				//keep track of how many points are left
				pointsLeft--;
				if (pointsLeft == 0) done = true;
				
			}
		}
		
		return abilityList;
	}
	
};

//manages abilities and player skill trees
class AbilityManager
{
	public:
		//CONSTRUCTOR: set sizes for pool vectors
		AbilityManager() 
		{
			std::vector< std::vector<Ability> > c;
			std::vector<Ability> t;
			
			//init category vectors
			for (unsigned int i = 0; i < CATEGORYCAP; ++i)
			{
				playerAbilityPool.push_back(c);
				//init type vectors
				for (unsigned int j = 0; j < TYPECAP; ++j)
				{
					playerAbilityPool[i].push_back(t);
				}
			}
			
			load_Abilities();
			load_Trees();
		}
		
		//controls which abilities can be obtained first for each player
		SkillTree p1AbilityTree;
		SkillTree p2AbilityTree;
		
		//get all abilities for a player
		std::vector< std::vector< std::vector<Ability> > > get_PlayerAbilityPool() const;
		
		//get all abilities for e0
		std::vector< std::vector< std::vector<Ability> > > get_E0AbilityPool() const;
		//get all abilities for e1
		std::vector< std::vector< std::vector<Ability> > > get_E1AbilityPool() const;
		//get all abilities for e2
		std::vector< std::vector< std::vector<Ability> > > get_E2AbilityPool() const;
		//get all abilities for e3
		std::vector< std::vector< std::vector<Ability> > > get_E3AbilityPool() const;
		
	private:
		//name of each file to read
		std::string filename;
	
		//manages ability category
		enum AbilityCategory {Attack_C, Support_C, Debuff_C};
		//manage ability types of all ability categories
		enum AttackAbilityType {Charged_T, Pierce_T, Area_T, Rapid_T};
		enum SupportAbilityType {StatBuff_T};
		enum DebuffAbilityType {StatDebuff_T};
		
		//player pool
		std::vector< std::vector< std::vector<Ability> > > playerAbilityPool;
		//enemy pools
		std::vector< std::vector< std::vector<Ability> > > e0AbilityPool;
		std::vector< std::vector< std::vector<Ability> > > e1AbilityPool;
		std::vector< std::vector< std::vector<Ability> > > e2AbilityPool;
		std::vector< std::vector< std::vector<Ability> > > e3AbilityPool;
		
		//loads all possible abilities
		void load_Abilities();
		//assign ability to correct character pool
		void assign_ToAbilityPool(Ability a, std::vector<std::string> usage, unsigned int category, unsigned int type);
		
		//fill player trees
		void load_Trees();
		//given id, search for ability in player ability list
		Ability* find_Ability(unsigned int id);
};
#endif
