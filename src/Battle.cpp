#include "Battle.h"

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//start battle
bool start_Battle()
{
	
}

//assign battle log
void Battle::assign_BattleLog(Player p1, Player p2, vector<Figment> figmentlist)
{
	//add tylor and liza to battlelog 
	Character* tylor = &p1;
	Character* liza = &p2;	
	battlelog.insert(pair<int, Character*>(100 - tylor->stats.get_Haste(), tylor));
	battlelog.insert(pair<int, Character*>(100 - liza->stats.get_Haste(), liza));

	//ERROR: no figment to fight
	if (!figmentlist.size()) 
	{	
		cerr << "No figment to fight. exiting" << endl;
		exit(1);
	}	

	//add all figments to battle log
	for (unsigned int i = 0; i < figmentlist.size(); ++i)
	{
		Character* figment = &figmentlist[i];
		battlelog.insert(pair<int, Character*>(100 - figment->stats.get_Haste(), figment));
	}	
}
