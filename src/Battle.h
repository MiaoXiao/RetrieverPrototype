#ifndef BATTLE_H
#define BATTLE_H

#include "Globals.h"
#include "Player.h"
#include "Figment.h"

#include <map>
#include <vector>

//manages and directs character decisions. alters player objects at the end of the battle.
//manages battle prompts
class Battle
{
	public:
		//CONSTRUCTOR: construct battle using both players and vector of figments
		Battle(Player* p, Player* p1, Player* p2, const int area, const unsigned int initialfigments):
			p(p),
			p1(p1),
			p2(p2),
			area(area)
		{ 
			int count = 0;
			//check if valid number of figments
			if (initialfigments > 6 || initialfigments <= 0)
			{
				std::cout << "Invalid number of figments. Exiting." << std::endl;
				exit(1);
			}
			runsuccessful = false;
			
			//spawn figments and populate vector
			while (count < initialfigments)
			{
				switch (area)
				{
					case Starting_A:
						Figment f(Enemy::PATH + "e0_stats", count, 0, 0);
						figmentlist.push_back(f);
						break;
				}
				count++;
			}
		}

		//begin battle. return true if player wins or escapes
		bool start_Battle();
		
	private:
		//enum for different battle menus
		enum MenuState {ChooseAction_S, ChooseTarget_S, ChooseAbility_S, ChooseItem_S, CheckEnergy_S, Prompt_S, Done_S};
		//enum for player decisions
		enum PlayerChoice {Swing, Ability, Defend, Item, Wait, Run};
		//enum for target
		enum Target {Enemy0, Enemy1, Enemy2, Enemy3, Enemy4, Enemy5, All};
		//enum for areas
		enum Area {Starting_A};
		
		//set to true if player succesfully runs
		bool runsuccessful;
		
		//player references
		Player* p;		
		Player* p1;
		Player* p2;
		
		//area id
		int area;
		
		//list of all figments in battle
		std::vector<Figment> figmentlist;		

		//multimap of battlelog
		std::multimap<float, Character*> battlelog;
		
		//get gcd of 2 numbers
		int gcd(int a, int b);
		
		//get lcd of 2 numbers
		int lcd(int a, int b);
		
		//get lcd of all possible units' reaction in battle
		int getall_Lcd(int a, int b, int c, int d, int e, int f, int g, int h);
		
		//compare haste between players and figments. assign battlelog of turn order
		void assign_BattleLog();
		
		//choose action menu
		void chooseAction_State(int &state, int &lastaction);
		
		//choose target menu
		void chooseTarget_State(int &state, int &lastaction, int &target);
		
		//choose ability menu
		void chooseAbility_State(int &state, int &lastaction);
		
		//choose item menu
		void chooseItem_State(int &state, int &lastaction);
		
		//calculate energy, check if action is possible. if not, go back to choose action.
		void checkEnergy_State(int &state, int lastaction, int &energychange, Character *c);
		
		//calculate outcome menu
		void prompt_State(int lastaction, int target, int energychange, Character* c);
		
		//make decision in combat, based on current turn
		void combatDecision(Character* c);

		//add loot to player: exp to tylor, exp to liza, digits
		void add_Loot(const unsigned int expT, const unsigned int expL, const unsigned int digits);
		
		//DEBUG: display complete turn order
		void show_TurnOrder();
		
		//DEBUG: show active figment vector, set to true if showing all stats
		void show_ActiveFigments(const bool allstats) const;
};

#endif
