#include "Battle.h"

#include <string>
#include <stdlib.h>

using namespace std;

//assign battle log
void Battle::assign_BattleLog(Player p1, Player p2, vector<Figment> figmentlist)
{
	//add tylor and liza to battlelog 
	Character* tylor = &p1;
	Character* liza = &p2;	
	battlelog.insert(pair<int, Character*>(tylor->stats.get_Haste(), tylor));
	battlelog.insert(pair<int, Character*>(liza->stats.get_Haste(), liza));

	//ERROR: no figment to fight
	if (!figmentlist.size()) exit(1);	

	//add all figments to battle log
	for (unsigned int i = 0; i < figmentlist.size(); ++i)
	{
		Character* figment = &figmentlist[i];
		battlelog.insert(pair<int, Character*>(figment->stats.get_Haste(), figment));
	}	
}
