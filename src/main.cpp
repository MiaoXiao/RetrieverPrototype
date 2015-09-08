#include "Info.h"

#include "Player.h"
#include "Figment.h"
#include "Battle.h"

using namespace std;

int main() 
{
	//file path for stats
	string statpath = "src/stats/";
	
	Info loadinfo;

	srand(time(0));	

	vector<Figment> figmentlist;

	Player tylor(statpath + "p0_stats");
	Player liza(statpath + "p1_stats");
	cout << endl;
	
	Battle battle1(&tylor, &liza, 0, 1, loadinfo);
	Battle battle2(&tylor, &liza, 0, 1, loadinfo);
	
	battle1.start_Battle();
	battle2.start_Battle();
}
