#ifndef BATTLE_H
#define BATTLE_H

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
		Battle(Player* p, Player* p1, Player* p2, std::vector<Figment> figmentlist):
			p(p),
			p1(p1),
			p2(p2),
			figmentlist(figmentlist) { }

		//begin battle. return true if player wins
		bool start_Battle();
		
	private:
		//enum for player decisions
		enum PlayerChoice {Swing, Ability, Defend, Item, Wait, Run};
		//enum for target
		enum Target {Enemy0, Enemy1, Enemy2, Enemy3, Enemy4, Enemy5, All};
		
		Player* p;		
		Player* p1;
		Player* p2;
		
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
	
		//make decision in combat, based on current turn
		void combatDecision(Character* c);

		//add loot to player
		//exp to tylor, exp to liza, digits
		void add_Loot(const unsigned int expT, const unsigned int expL, const unsigned int digits);
		
		//DEBUG: display complete turn order
		void show_TurnOrder();
};

#endif
