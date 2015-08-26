#include "Ability.h"
#include "Charged.h"

#include "Player.h"
#include "Figment.h"
#include "Battle.h"

using namespace std;

//loads all possible abilities
vector<Ability*> load_Abilities()
{
	//type of ability
	string abilityType;
	//name of ability
	string abilityName;
	//extra damage that ability can do, based off swing damage
	string damageModifier;
	//description of ability
	string description;
	//which character can use the ability
	vector<string> usage;
}

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
	
	Battle battle(&player, &tylor, &liza, 0, 1);
	battle.start_Battle(); 
}
