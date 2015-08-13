#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Figment.h"

#include <map>
#include <vector>

//manages and directs character decisions. alters player objects at the end of the battle
class Battle
{
	public:
		//CONSTRUCTOR: construct battle using both players and vector of figments
		Battle(Player &p, Player &p1, Player &p2, std::vector<Figment> &figmentlist):
			p(p),
			p1(p1),
			p2(p2),
			figmentlist(figmentlist) { }

		//begin battle. return true if player wins
		bool start_Battle();
	private:
		//enum for player decisions
		enum PlayerChoice {Swing, Ability, Defend, Item, Run};
		//enum for target
		enum Target {Enemy0, Enemy1, Enemy2, Enemy3, Enemy4, Enemy5, All};
		
		Player p;		
		Player p1;
		Player p2;
		
		std::vector<Figment> &figmentlist;		

		//multimap of battlelog
		std::multimap<int, Character*> battlelog;
	
		//make decision in combat, based on current turn
		void combatDecision(Character* c);
		
		//compare haste between players and figments. assign battlelog of turn order
		void assign_BattleLog();

		//add loot to player
		//exp to tylor, exp to liza, digits
		void add_Loot(const unsigned int expT, const unsigned int expL, const unsigned int digits);

		

		
};

#endif
