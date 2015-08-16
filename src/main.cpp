#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "Player.h"
#include "Figment.h"
#include "Battle.h"

using namespace std;

int main() 
{
	string statpath = "src/stats/";
	srand(time(0));	

	vector<Figment> figmentlist;

	Player player;
	Player tylor(statpath + "p0_stats");
	Player liza(statpath + "p1_stats");

	Figment f1(statpath + "e2_stats", 1, 0, 0);
	//f1.showall_Stats();
	cout << endl;
	
	figmentlist.push_back(f1);	

	Battle battle(&player, &tylor, &liza, figmentlist);
	battle.start_Battle(); 
}
