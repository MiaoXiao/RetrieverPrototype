#include "Load.h"
#include "Ability.h"

#include "Player.h"
#include "Figment.h"
#include "Battle.h"

using namespace std;

int main() 
{
	//file path for stats
	string statpath = "src/stats/";
	
	Load abilityInfo;
	abilityInfo.load_Abilities();

	srand(time(0));	

	vector<Figment> figmentlist;

	Player tylor(statpath + "p0_stats");
	Player liza(statpath + "p1_stats");
	cout << endl;
	
	Battle battle(&tylor, &liza, 0, 1, abilityInfo);
	battle.start_Battle(); 
}
