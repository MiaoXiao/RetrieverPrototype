#include "Battle.h"
#include "Globals.h"

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
	show_TurnOrder();
	
	unsigned int turnnumber = 0;
	while (true)
	{
		for (multimap<float, Character*>::iterator it = battlelog.begin(); it != battlelog.end(); ++it)
		{
			cout << "Turn Number: " << turnnumber << endl;
			combatDecision((*it).second);
			
			//battle is finished if no figments left in battle, or both tylor and liza are wiped out
			if (figmentlist.empty()) return true;
			else if (p1->isAlive == false && p2->isAlive == false) return false;
			turnnumber++;
		}
	}
}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
//get gcd of 2 numbers
int Battle::gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

//get lcd of 2 numbers
int Battle::lcd(int a, int b) { return abs(a * b) / (gcd(a, b)); }

//get lcd of all possible units' reaction in battle
int Battle::getall_Lcd(int a, int b, int c, int d, int e, int f, int g, int h) 
{
		return lcd(a, lcd(b, lcd(c, lcd(d, lcd(e, lcd(f, lcd(g, h)))))));
}

//assign battle log
void Battle::assign_BattleLog()
{
	//ERROR: no figment to fight
	if (!figmentlist.size()) 
	{	
		cerr << "No figment to fight. Exiting." << endl;
		exit(1);
	}	
	
	//clear any existing battle log
	battlelog.clear();
	
	//stores reaction for tylor and liza
	unsigned int r_t = p1->stats.get_Reaction();
	unsigned int r_l = p2->stats.get_Reaction();

	vector<unsigned int> r_enemy(6, 1);
	//store enemy reaction in vector
	for (unsigned int i = 0; i < figmentlist.size(); ++i) { r_enemy[i] = (&figmentlist[i])->stats.get_Reaction(); }	
	
	//get entire gcd
	const int entireGCD = getall_Lcd(r_t, r_l, r_enemy[0], r_enemy[1], r_enemy[2], r_enemy[3], r_enemy[4], r_enemy[5]);
	//cout << r_t << " " << r_l << " " << r_enemy[0] << " " << r_enemy[1] << endl;
	cout << "LCD: " << entireGCD << endl;
	
	//get all tylor turns
	int reactionvalue = r_t;
	while (r_t <= entireGCD)
	{
		cout << "tylor" << endl;
		battlelog.insert(pair<float, Character*>(r_t, p1));
		r_t += reactionvalue;
	}
	//get all liza turns
	reactionvalue = r_l;
	while (r_l <= entireGCD)
	{
		cout << "liza" << endl;
		battlelog.insert(pair<int, Character*>(r_l, p2));
		r_l += reactionvalue;
	}
	//get all enemy turns
	for (unsigned int i = 0; i < figmentlist.size(); ++i)
	{
		reactionvalue = r_enemy[i];
		while (r_enemy[i] <= entireGCD)
		{
			//cout << "enemy" << endl;
			battlelog.insert(pair<float, Character*>(r_enemy[i], &figmentlist[i]));
			//check if a player and an enemy have the same reaction, then choose one randomly to go first
			/*
			if (battlelog.count(r_enemy[i]) > 1)
			{
				bool playerFirstTurn = false;
				cout << "calculating 50percent chance..." << endl;
				if (chanceToOccur(0.5))
				{
					playerFirstTurn = true;
				}
				
				for (std::multimap<float, Character*>::iterator it = battlelog.equal_range(r_enemy[i]).first; it!=battlelog.equal_range(r_enemy[i]).second; ++it)
				{
					//only look at player
					if ((*it).second->isPlayer)
					{
						int saveReaction = ((*it).first);
						Character* tempc = ((*it).second);
						battlelog.erase(it);
						
						if (playerFirstTurn)
						{
							battlelog.insert(pair<float, Character*>(saveReaction -= 0.5, tempc));
						}
						else
						{
							battlelog.insert(pair<float, Character*>(saveReaction += 0.5, tempc));
						}
					}
				}
			}*/
			
			r_enemy[i] += reactionvalue;
		}
	}
}

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
		//prompt choice
		do
		{
			badInput = false;
			
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
			//prompt choose target
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
			{
				cout << c->get_Name() << " swings at " << figmentlist[target].get_Name() << "!" << endl;
				//check if attack is evaded
				
				//calculate damage
				int d = c->inflict_Damage();
			
				cout << figmentlist[target].get_Name() << " takes " << d << " damage!" << endl;
				figmentlist[target].take_Damage(d);
				
				//remove target from battlelog and figmentlist if destroyed
				if (!figmentlist[target].isAlive)
				{
					battlelog.erase(target);
					cout << figmentlist[target].get_Name() << " is defeated!" << endl;
					figmentlist.erase(figmentlist.begin()+target);
				}
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

//add loot to player
//exp to tylor, exp to liza, digits
void Battle::add_Loot(const unsigned int expT, const unsigned int expL, const unsigned int digits)
{
	if (p1->isAlive)
	{
		p1->level.experience += expT;
	}
	if (p2->isAlive)
	{
		p2->level.experience += expL;		
	}
	p->set_Digits(p->get_Digits() + digits);
}

//DEBUG: display complete turn order for one cycle
void Battle::show_TurnOrder()
{
	cout << endl << "TURN ORDER" << endl;
	int i = 0;
	for (multimap<float, Character*>::iterator it = battlelog.begin(); it != battlelog.end(); ++it)
	{
		cout << i << ": " << (*it).second->get_Name() << " on timeline " << (*it).first << endl;
		++i;
	}
	cout << endl;
}
