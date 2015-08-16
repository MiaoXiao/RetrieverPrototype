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
	
	unsigned int turnnumber = 0;
	while (true)
	{
		for (multimap<float, Character*>::iterator it = battlelog.begin(); it != battlelog.end(); ++it)
		{
			cout << "Turn Number: " << turnnumber << endl;
			combatDecision((*it).second);
			
			//battle is finished if no figments left in battle, or both tylor and liza are wiped out, or players succesfully run
			if (figmentlist.empty()) return true;
			else if (p1->isAlive == false && p2->isAlive == false) return false;
			else if (runsuccessful) return true;
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
	//cout << "LCD: " << entireGCD << endl;
	
	//get all tylor turns
	int reactionvalue = r_t;
	while (r_t <= entireGCD)
	{
		//cout << "tylor" << endl;
		battlelog.insert(pair<float, Character*>(r_t, p1));
		r_t += reactionvalue;
	}
	//get all liza turns
	reactionvalue = r_l;
	while (r_l <= entireGCD)
	{
		//cout << "liza" << endl;
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

//choose action menu
void Battle::chooseAction_State(int &state, int &lastaction)
{
	int choice;
	cout << "0 to attack, 1 to use ability, 2 to defend, 3 to use item, 4 to wait, 5 to run" << endl;
	cin >> choice;
	if (choice < 0 && choice > 5)
	{
		cout << "Not a valid input, try again." << endl;
		state = ChooseAction_S;
	}
	else
	{
		switch(choice)
		{
			case Swing:
				state = CheckEnergy_S;
				lastaction = Swing;
				break;
			case Ability:
				state = ChooseAbility_S;
				lastaction = Ability;
				break;
			case Defend:
				state = CheckEnergy_S;
				lastaction = Defend;
				break;
			case Item:
				state = ChooseItem_S;
				lastaction = Item;
				break;
			case Wait:
				state = CheckEnergy_S;
				lastaction = Wait;
				break;
			case Run:
				state = CheckEnergy_S;
				lastaction = Run;
				break;
			default:
				cout << "ChooseAction state error. Exiting" << endl;
				exit(1);
				break;
		}
	}
}

//choose target menu
void Battle::chooseTarget_State(int &state, int &lastaction, int &target)
{
		int choice;
		//prompt choose target
		cout << "Choose target between 0 and " << figmentlist.size() - 1 << endl;
		cin >> target;
		if (target < 0 || target > figmentlist.size() - 1)
		{
			cout << "Not a valid target, please enter again." << endl;
			state = ChooseTarget_S;
			//reset target to default
			target = 0;
		}
		else state = Prompt_S;
		lastaction = Swing;
}

//choose ability menu
void Battle::chooseAbility_State(int &state, int &lastaction)
{
	lastaction = Ability;
	state = Prompt_S;
}

//choose item menu
void Battle::chooseItem_State(int &state, int &lastaction)
{
	lastaction = Item;
	state = Prompt_S;
}

//calculate energy, check if action is possible. if not, go back to choose action.
void Battle::checkEnergy_State(int &state, int lastaction, int &energychange, Character *c)
{
	//get energy change
	energychange = c->get_EnergyDifference(lastaction);
	//check if action is possible with current energy
	if (c->stats.get_CurrEnergy() + energychange < 0)
	{
		cout << "You do not have enough energy to complete this action!" << endl;
		state = ChooseAction_S;
		//reset to default
		energychange = 0;
	}
	else state = Prompt_S;
}

//outcome menu
void Battle::prompt_State(int lastaction, int target, int energychange, Character* c)
{
	//calculate energy addition/reduction for character
	c->stats.set_CurrEnergy(c->stats.get_CurrEnergy() + energychange);
	//based on last prompt, calculate action and display prompts
	switch (lastaction)
	{
		case Swing:
		{
				cout << c->get_Name() << " uses " << abs(energychange) << " energy and swings at " << figmentlist[target].get_Name() << "!" << endl;
				//check if attack is evaded
				if (figmentlist[target].check_Evasion())
				{
					cout << figmentlist[target].get_Name() << " evades the attack!" << endl;
				}
				else
				{
					//calculate damage
					int d = c->inflict_Damage();
					
					//check critical
					if (c->check_Critical()) 
					{
						d *= c->stats.get_FocusMultiplier();
						cout << c->get_Name() << " lands a critical attack!" << endl;
					}
					
					//check if enemy was defending
					if (figmentlist[target].status.get_Defense())
					{
						int rp = figmentlist[target].stats.get_ReflectPercentage();
						c->take_Retaliation(d, rp);
						
						//damage done back to attacker
						int rd = rp * d;
						//damage done to defender
						d *= (1 - rp);
						cout << figmentlist[target].get_Name() << " defends against the attack, and returns " << rd 
							<< " damage back to " << c->get_Name() << "!" << endl;
					}
					
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
		}
		case Ability:
			break;
		case Defend:
			c->status.set_Defense(true);
			cout << c->get_Name() << " forms a defensive stance." << endl;
			break;
		case Item:
		case Wait:
			cout << c->get_Name() << " waits and catches " << c->pronoun << " breath, restoring " << energychange << " energy." << endl;
			break;
		case Run:
			cout << c->get_Name() << " and company use " << abs(energychange) << " energy in an attempt to run away!" << endl;
			if (Probability::chanceToOccur(Globals::RUNPROBABILITY))
			{
				cout << "Run was successful!" << endl;
				runsuccessful = true;
			}
			else cout << "Running was not successful!" << endl;
			break;
	}
}

//make decision in combat based on selected character's turn
void Battle::combatDecision(Character* c)
{	
	cout << "It is " << c->get_Name() << "'s turn" << endl;
	
	//default target;
	int target = 0;
	//change in energy for an action
	int energychange = 0;
	//whether turn is over  or not
	bool nextturn = false;
	//current state, set initial state
	int state = ChooseAction_S;
	//last action - used for determining what prompt to use
	int lastaction;
	
	//decide if player or enemy turn
	if (c->isPlayer)
	{
		//reset back to neutral stance
		c->status.set_Defense(false);
		
		//used to transition between different menus during a battle
		while (!nextturn)
		{
			switch (state)
			{
					case ChooseAction_S:
						chooseAction_State(state, lastaction);
						break;
					case ChooseTarget_S:
						chooseTarget_State(state, lastaction, target);
						break;
					case ChooseAbility_S:
						chooseAbility_State(state, lastaction);
						break;
					case ChooseItem_S:
						chooseItem_State(state, lastaction);
						break;
					case CheckEnergy_S:
						checkEnergy_State(state, lastaction, energychange, c);
						break;
					case Prompt_S:
						prompt_State(lastaction, target, energychange, c);
						nextturn = true;
						break;
			}
		}
	}
	
	c->showall_Stats();
	//figmentlist[target].showall_Stats();
		
}

//add loot to player
//exp to tylor, exp to liza, digits
void Battle::add_Loot(const unsigned int expT, const unsigned int expL, const unsigned int digits)
{
	if (p1->isAlive)
	{
		p1->level.change_Level(expT);
	}
	if (p2->isAlive)
	{
		p2->level.change_Experience(expL);		
	}
	p->change_Digits(digits);
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
