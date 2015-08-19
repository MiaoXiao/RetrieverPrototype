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

	//f1.showall_Stats();
	cout << endl;
	
	Battle battle(&player, &tylor, &liza, 0, 3);
	battle.start_Battle(); 
}
