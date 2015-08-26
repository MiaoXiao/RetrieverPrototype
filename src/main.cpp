#include "Load.h"
#include "Ability.h"
#include "Charged.h"

#include "Player.h"
#include "Figment.h"
#include "Battle.h"

using namespace std;

int main() 
{
	Load abilityInfo;
	abilityInfo.load_Abilities();
	
	string statpath = "src/stats/";
	srand(time(0));	

	vector<Figment> figmentlist;

	Player tylor(statpath + "p0_stats", abilityInfo.get_P1Abilities());
	Player liza(statpath + "p1_stats", abilityInfo.get_P2Abilities());
	cout << endl;
	
	Battle battle(&tylor, &liza, 0, 1);
	battle.start_Battle(); 
}
