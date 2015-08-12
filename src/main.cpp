#include <iostream>
#include <vector>

#include "Player.h"
#include "Figment.h"
#include "Battle.h"

using namespace std;

int main() 
{
	vector<Figment> figmentlist;

	Player player;
	Player tylor("Tylor");
	Player liza("Liza");

	Figment f1(0, 1, 0, 0);
	f1.showall_Stats();
	
	figmentlist.push_back(f1);	

	Battle battle(player, tylor, liza, figmentlist);
	battle.start_Battle();
}
