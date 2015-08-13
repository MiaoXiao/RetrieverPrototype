#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Figment.h"

#include <map>
#include <vector>

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
		Player p;		
		Player p1;
		Player p2;
		
		std::vector<Figment> &figmentlist;		


		//multimap of battlelog
		std::multimap<int, Character*> battlelog;
		
		//compare haste between players and figments. assign battlelog of turn order
		void assign_BattleLog();

		
};

#endif
