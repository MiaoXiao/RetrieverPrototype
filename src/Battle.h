#ifndef BATTLE_H
#define BATTLE_H

#include "Globals.h"
#include "Load.h"
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

//manages and directs character decisions. alters player objects at the end of the battle.
//manages battle prompts
class Battle
{
	public:
		//CONSTRUCTOR: construct battle using both players and vector of figments
		Battle(Player* p1, Player* p2, const int area, const unsigned int initialfigments, Load abilityInfo):
			p1(p1),
			p2(p2),
			area(area),
			abilityInfo(abilityInfo)
		{ 
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
						Figment f(Enemy::PATH + "e1_stats", count, 0, 0);
						figmentlist.push_back(f);
						break;
				}
				count++;
			}
			
			//TODO: assign figments their abilities
			
			runsuccessful = false;
		}

		//begin battle. return true if player wins or escapes
		bool start_Battle();
		//end battle
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
		
		//holds all abilities
		Load abilityInfo;
		
		
		
		//set to true if player succesfully runs
		bool runsuccessful;
		
		//current state in battle menu
		int state;
		//last action player attempted to do
		int lastaction;
		
		//player references	
		Player* p1;
		Player* p2;
		//list of all figments in battle
		std::vector<Figment> figmentlist;		

		//battlelog
		std::multimap<float, Character*> battlelog;
		
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
		void chooseAbility_State(Character* player);
		//choose item menu
		void chooseItem_State();
		//calculate energy, check if action is possible. if not, go back to choose action.
		void checkEnergy_State(int &energychange, Character *player);
		//calculate outcome menu
		void prompt_State(const int target, const int energychange, Character* player);
		
		//make decision in combat, based on current turn
		void combatDecision(Character* c);

		//add loot to player: exp and money
		void add_Loot(const unsigned int exp, const unsigned int digits);
		
		//check to see if specified player leveled up
		void checkLevelUp(Player* player);
		
		//DEBUG: display complete turn order
		void show_TurnOrder();
		//DEBUG: show active figment vector, set to true if showing all stats
		void show_ActiveFigments(const bool allstats) const;
};

#endif
