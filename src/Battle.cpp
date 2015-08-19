#include "Battle.h"

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
				//if character is alive, calculate their turn
				if (((*it).second->status.get_IsAlive()))
				{
					show_ActiveFigments(true);
					cout << "Turn Number: " << turnnumber << endl;
					combatDecision((*it).second);
					
					//battle is finished if no figments left in battle, or both tylor and liza are wiped out, or players succesfully run
					if (figmentlist.empty()) return true;
					else if (!(p1->status.get_IsAlive()) && !(p2->status.get_IsAlive())) return false;
					else if (runsuccessful) return true;
					turnnumber++;
				}
		}
	}
}

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
//get gcd of 2 numbers
int Battle::gcd(unsigned int a, unsigned int b) { return b == 0 ? a : gcd(b, a % b); }

//get lcd of 2 numbers
int Battle::lcd(unsigned int a, unsigned int b) { return abs(a * b) / (gcd(a, b)); }

//get lcd of all possible units' reaction in battle
int Battle::getall_Lcd(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h) 
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
void Battle::chooseAction_State()
{
	int choice;
	cout << "'0' to attack, '1' to use ability, '2' to defend, '3' to use item, '4' to wait, '5' to run" << endl;
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
				cout << "ChooseAction state error. Exiting." << endl;
				exit(1);
				break;
		}
	}
}

//choose target menu
void Battle::chooseTarget_State(int &target)
{
		//prompt choose target
		cout << "Choose target between '0' and '" << figmentlist.size() - 1 << "'" << endl;
		cout << "'9' to go back." << endl;
		cin >> target;
		if (target == 9) state = ChooseAction_S;
		else if (target < 0 || target > figmentlist.size() - 1) //check if input is valid
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
void Battle::chooseAbility_State()
{
	lastaction = Ability;
	state = Prompt_S;
}

//choose item menu
void Battle::chooseItem_State()
{
	lastaction = Item;
	state = Prompt_S;
}

//calculate energy, check if action is possible. if not, go back to choose action.
void Battle::checkEnergy_State(int &energychange, Character *c)
{
	//get energy change
	energychange = c->get_EnergyDifference(lastaction);
	//check if action is possible with current energy
	if (c->stats.get_CurrEnergy() + energychange < 0)
	{
		//reset to default
		energychange = 0;
		cout << "You do not have enough energy to complete this action!" << endl;
		state = ChooseAction_S;
	}
	else if (figmentlist.size() > 1 && (lastaction == Swing || lastaction == Ability)) //check if target needs to be specified when swinging or using ability
	{
		state = ChooseTarget_S;
	}
	else state = Prompt_S; //only one target
}

//outcome menu
void Battle::prompt_State(const int target, const int energychange, Character* c)
{
	//calculate energy addition/reduction for character
	c->stats.set_CurrEnergy(c->stats.get_CurrEnergy() + energychange);
	//based on last prompt, calculate action and display prompts
	switch (lastaction)
	{
		case Swing:
		{
				cout << c->get_Name() << " uses " << abs(energychange) << " energy and swings at " << figmentlist[target].get_Name() << "!" << endl;
				figmentlist[target].take_Damage(figmentlist[target].get_Name(), figmentlist[target].check_Evasion(), figmentlist[target].status.get_Defending(), figmentlist[target].stats.get_ReflectPercentage(), c);
				
				//remove target from battlelog and figmentlist if figment is destroyed
				if (!figmentlist[target].status.get_IsAlive())
				{
					//PROMPT
					cout << figmentlist[target].get_Name() << " is defeated!" << endl;
					
					//erase figment
					figmentlist.erase(figmentlist.begin() + (target));
				}
				
				break;
		}
		case Ability:
			break;
		case Defend:
			c->status.set_Defending(true);
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
	//PROMPT
	cout << "It is " << c->get_Name() << "'s turn" << endl;
	
	//reset initial state
	state = ChooseAction_S;
	
	//default target;
	int target = 0;
	//change in energy for an action
	int energychange = 0;
	//whether turn is over  or not
	bool nextturn = false;
	
	if (c->status.get_IsPlayer()) //PLAYER TURN
	{
		//reset back to neutral stance
		c->status.set_Defending(false);
		
		//used to transition between different menus during a battle
		while (!nextturn)
		{
			switch (state)
			{
					case ChooseAction_S:
						chooseAction_State();
						break;
					case ChooseTarget_S:
						chooseTarget_State(target);
						break;
					case ChooseAbility_S:
						chooseAbility_State();
						break;
					case ChooseItem_S:
						chooseItem_State();
						break;
					case CheckEnergy_S:
						checkEnergy_State(energychange, c);
						break;
					case Prompt_S:
						prompt_State(target, energychange, c);
						nextturn = true;
						break;
			}
		}
	}
	else // ENEMY TURN
	{
		int enemyAction = Probability::multipleChanceToOccur(0.5, 0.25, 0.25);
		switch (enemyAction)
		{
			case Swing:
				
				break;
			case Ability:
				break;
			case Defend:
				break;
			default:
				cerr << "Invalid enemy action. Exiting." << endl;
				exit(1);
		}
	}
	//figmentlist[target].showall_Stats();
}

//add loot to player: exp and money
void Battle::add_Loot(const unsigned int exp, const unsigned int digits)
{
	if (p1->status.get_IsAlive())
	{
		p1->level.change_Level(exp);
	}
	if (p2->status.get_IsAlive())
	{
		p2->level.change_Experience(exp);		
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

//DEBUG: show active figment vector, set to true if showing all stats
void Battle::show_ActiveFigments(const bool allstats) const
{
	
	for (unsigned int i = 0; i < figmentlist.size(); ++i)
	{
		cout << i << ": " << figmentlist[i].get_Name() << endl;
		if (allstats) figmentlist[i].stats.show_Stats();
	}
}
