#ifndef BATTLE_H
#define BATTLE_H

#include "Globals.h"
#include "Info.h"
#include "Player.h"
#include "Figment.h"

#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>

//maximum number of figments the player can fight at once
#define MAXFIGMENTS 6

//path for figment stats
#define ENEMYPATH std::string("src/stats/")

//ability points given for each level
#define ABILITYPOINTS 1

//manages and directs character decisions. alters player objects at the end of the battle.
//manages battle prompts
class Battle
{
	public:
		//CONSTRUCTOR: construct battle using both players and vector of figments
		Battle(Player* p1, Player* p2, const int area, const unsigned int initialfigments, Info loadInfo):
			area(area),
			loadInfo(loadInfo)
		{ 
			//assign player objects to vector
			playerList.push_back(p1);
			playerList.push_back(p2);
			
			//check if valid number of enemies
			int count = 0;
			//check if valid number of figments
			if (initialfigments > MAXFIGMENTS || initialfigments <= 0)
			{
				std::cout << "Invalid number of figments. Exiting." << std::endl;
				exit(1);
			}
			
			//spawn figments and populate figment vector
			while (count < initialfigments)
			{
				switch (area)
				{
					case Starting_A:
						Figment f(ENEMYPATH + "e0_stats", count, 5, 0);
						figmentlist.push_back(f);
						break;
				}
				count++;
			}
			
			//TODO: assign figments their abilities
			
			//default values
			runsuccessful = false;
			
			//resize exp and digit vectors
			expFinal.push_back(0);
			expFinal.push_back(0);
			digitsFinal.push_back(0);
			digitsFinal.push_back(0);
			
			//std::cout << "id1: " << p1->get_Id() << std::endl;
			//std::cout << "id2: " << p2->get_Id() << std::endl;
		}

		//begin battle. return true if player wins or escapes
		bool start_Battle();
		//end battle, reset status, check for level up
		void end_Battle();
		
	private:
		//enum for different battle menus
		enum MenuState {ChooseAction_S, ChooseTarget_S, ChooseAbility_S, ChooseItem_S, CheckEnergy_S, Prompt_S, Done_S};
		//enum for character decisions
		enum CharacterChoice {Swing, Ability, Defend, Item, Wait, Run};
		//enum for areas
		enum Area {Starting_A};
		//area id
		int area;
		
		//holds all loading info for abilities and items
		Info loadInfo;
		//set to true if curent ability is single target only
		bool abilityChooseTarget;
		//id of ability to use
		unsigned int abilityId;
		
		//set to true if player succesfully runs
		bool runsuccessful;
		
		//current state in battle menu
		int state;
		//last action player attempted to do
		int lastaction;
		
		//player references	
		//Player* p1;
		//Player* p2;
		//list of avaliable players
		std::vector<Player*> playerList;
		//list of all figments in battle
		std::vector<Figment> figmentlist;		

		//battlelog
		std::multimap<float, Character*> battlelog;
		
		//final exp awarded to both players
		std::vector<unsigned int> expFinal;
		//unsigned int p1ExpFinal;
		//unsigned int p2ExpFinal;
		//final digits awarded to both players
		std::vector<unsigned int> digitsFinal;
		//unsigned int p1DigitsFinal;
		//unsigned int p2DigitsFinal;
		
		//get gcd of 2 numbers
		int gcd(unsigned int a, unsigned int b);
		//get lcd of 2 numbers
		int lcd(unsigned int a, unsigned int b);
		//get lcd of all possible units' reaction in battle
		int getall_Lcd(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h);
		
		//compare haste between players and figments. assign battlelog of turn order
		void assign_BattleLog();
		
		//choose action menu
		void chooseAction_State();
		//choose target menu
		void chooseTarget_State(int &target);
		//choose ability menu
		void chooseAbility_State(int &energychange, Character* player);
		//choose item menu
		void chooseItem_State();
		//calculate energy, check if action is possible. if not, go back to choose action.
		void checkEnergy_State(int &energychange, Character *player);
		//calculate outcome menu
		void prompt_State(const int target, const int energychange, Character* player);
		
		//check if any targeted enemies are defeated
		void check_Enemy(std::vector<Character*> allTargets);
		
		//make decision in combat, based on current turn
		void combatDecision(Character* c);
		
		//add loot to player: exp and money
		void add_Loot(const unsigned int exp, const unsigned int digits);
		//calculate possible items to give to player
		void add_Item(float itemfindprobability, unsigned int itemId);
		
		//level up 1 player
		void levelUp(Player* player);
		
		//DEBUG: display complete turn order
		void show_TurnOrder();
		//DEBUG: show active figment vector, set to true if showing all stats
		void show_ActiveFigments(const bool allstats) const;
};

#endif
