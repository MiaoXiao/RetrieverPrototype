#include "Battle.h"

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//start battle by creating initial battle log
//runs through all combat decisions
bool Battle::start_Battle()
{
	assign_BattleLog();
	for (multimap<int, Character*>::iterator it = battlelog.begin(); it != battlelog.end(); ++it)
	{
		combatDecision((*it).second);
		
		//battle is finished if no figments left in battle, or both tylor and liza are wiped out
		if (figmentlist.empty()) return true;
		else if (p1.isAlive == false && p2.isAlive == false) return false;
	}
}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
//make decision in combat based on selected character's turn
void Battle::combatDecision(Character* c)
{
	cout << "It is " << c->get_Name() << "'s turn" << endl;
	
	//choice of the player
	int choice;
	//target of player/figment. default is 0
	int target = 0;
	//sets to true if bad input
	bool badInput;
	
	//decide if player or enemy turn
	if (c->isPlayer)
	{
		do
		{
			badInput = false;
			
			//prompt ability
			cout << "0 to attack, 1 to use ability, 2 to defend, 3 to use item, 4 to run" << endl;
			cin >> choice;
			if (choice < 0 && choice > 4)
			{
				cout << "Not a valid input, try again" << endl;
				badInput = true;
			}
			else { badInput = false; }
		} while (badInput);
		
		//target selector if swing or ability and battling more than 1 figment
		if ((choice == Swing || choice == Ability) && figmentlist.size() > 1)
		{
			do
			{
				cout << "Choose target between 0 and " << figmentlist.size() - 1 << endl;
				cin >> target;
				if (target < 0 || target > figmentlist.size() - 1)
				{
					badInput = true;
					cout << "Not a valid target, please enter again" << endl;
				}
				else { badInput = false; }
			} while (badInput);
		}
		
		//run specified action on specified target
		switch (choice)
		{
			case Swing:
				cout << figmentlist[target].get_Name() << " takes " << c->inflict_Damage() << " damage!" << endl;
				figmentlist[target].take_Damage(c->inflict_Damage());
				
				//remove target from battlelog and figmentlist if destroyed
				if (!figmentlist[target].isAlive)
				{
					battlelog.erase(target);
					cout << figmentlist[target].get_Name() << " is defeated!" << endl;
					figmentlist.erase(figmentlist.begin()+target);
				}
				
				break;
			case Ability:
				break;
			 case Defend:
				break;
			case Item:
				break;
			 case Run:
				break;
			default:
				badInput = true;
				break;
		}
		
		figmentlist[target].showall_Stats();
		
	}
}

//assign battle log
void Battle::assign_BattleLog()
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

//add loot to player
//exp to tylor, exp to liza, digits
void Battle::add_Loot(const unsigned int expT, const unsigned int expL, const unsigned int digits)
{

}

