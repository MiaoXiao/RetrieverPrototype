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
				//get character name
				Character* c = (*it).second;
				
				//if character is alive, calculate their turn
				if ((c->status.get_IsAlive()))
				{
					//cout << p1->level.get_Experience();
					cout << p1->get_Name() << endl;
					p1->stats.show_Stats();
					cout << p2->get_Name() << endl;
					p2->stats.show_Stats();
					show_ActiveFigments(true);
					
					//at the start of turn, always set defending to false
					c->status.set_Defending(false);
					
					cout << "Turn Number: " << turnnumber << endl;
					//PROMPT
					cout << "It is " << c->get_Name() << "'s turn" << endl;
					
					//decide action
					combatDecision(c);
					
					//battle is finished if no figments left in battle, or both tylor and liza are wiped out, or players succesfully run
					if (figmentlist.empty() || runsuccessful)
					{
						end_Battle();
						return true;
					}
					else if (!(p1->status.get_IsAlive()) && !(p2->status.get_IsAlive())) 
					{
						return false;
					}
					turnnumber++;
				}
		}
	}
}

//end battle, reset status, check for level up
void Battle::end_Battle()
{
	string p1name = p1->get_Name();
	string p2name = p2->get_Name();
	
	if (runsuccessful) cout << "Although your party flees..." << endl;
	
	//tally exp and digits
	if (p1ExpFinal == p2ExpFinal) cout << p1name << " and " << p2name << " both earn " << p1ExpFinal << " experience." << endl;
	else cout << p1name << " earns " << p1ExpFinal << " experience and " << p2name << " earns " << p2ExpFinal << " experience." << endl;
	if (p1DigitsFinal == p2DigitsFinal) cout << p1name << " and " << p2name << " both earn " << p1DigitsFinal << " digits." << endl << endl; 
	else cout << p1name << " earns " << p1DigitsFinal << " digits and " << p2name << " earns " << p2DigitsFinal << " digits." << endl << endl;

	p1->status.reset_Status();
	p2->status.reset_Status();
	
	if (p1->level.checkLevelUp()) levelUp(p1);
	if (p2->level.checkLevelUp()) levelUp(p2);
	
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

//choose target menu, for swing attack or ability
void Battle::chooseTarget_State(int &target)
{
		//prompt choose target
		cout << "Choose target between '0' and '" << figmentlist.size() - 1 << "'" << endl;
		cout << "'9' to go back." << endl;
		cin >> target;
		if (target == 9 && lastaction == Ability) state = ChooseAbility_S;
		else if (target == 9) state = ChooseAction_S;
		else if (target < 0 || target > figmentlist.size() - 1) //check if input is valid
		{
			cout << "Not a valid target, please enter again." << endl;
			state = ChooseTarget_S;
			//reset target to default
			target = 0;		
		} 
		else state = Prompt_S;
}

//choose ability menu
void Battle::chooseAbility_State(int &energychange, Character* player)
{
	//shortcut for numb abilities
	int numbAbilities = player->abilities.get_Size();
	//shortcut for name
	string playerName = player->get_Name();
	
	if (numbAbilities == 0)
	{
		cout << playerName << " has no abilities to choose from." << endl;
		state = ChooseAction_S;
	}
	else
	{
		lastaction = Ability;
		int choice;
		
		//prompt choose target
		if (numbAbilities == 1) cout << playerName << " has 1 ability to choose from." << endl;
		else cout << playerName << " has " << numbAbilities << " abilities to choose from." << endl;
		
		cout << "Select an ability.";
		cout << "'9' to go back." << endl << endl;
		
		//display ability information
		for (unsigned int i = 0; i < numbAbilities; ++i)
		{
			//index pos
			unsigned int pos = player->abilities.get_AbilityList()[i];
			
			cout << i << ": " << loadInfo.p1AbilityTree.list[pos].ability->get_Name() << endl;
			cout << loadInfo.p1AbilityTree.list[pos].ability->get_Description() << endl << endl;
		}
		
		cin >> choice;
		if (choice == 9) state = ChooseAction_S;
		else if (choice < 0 || choice > numbAbilities - 1)
		{
			cout << "Not a valid ability, try again." << endl;
			state = ChooseAbility_S;
		}
		else
		{
			//set ability id
			abilityId = player->abilities.get_AbilityList()[choice];
			
			//check to see if this ability is already active
			if (player->abilities.get_CurrentChargeId() == abilityId)
			{
				cout << player->get_Name() << " is already charging an attack." << endl;
				state = ChooseAction_S;
			}
			else
			{
				//get energy change for that ability, decide if you need to choose target for ability
				if (player == p1)
				{
					energychange = loadInfo.p1AbilityTree.list[abilityId].ability->get_EnergyUsage();
					abilityChooseTarget = loadInfo.p1AbilityTree.list[abilityId].ability->get_SingleTarget();
				}
				else if (player == p2)
				{
					energychange = loadInfo.p2AbilityTree.list[abilityId].ability->get_EnergyUsage();
					abilityChooseTarget = loadInfo.p2AbilityTree.list[abilityId].ability->get_SingleTarget();
				}
				state = CheckEnergy_S;
			}
		}
	}
}

//choose item menu
void Battle::chooseItem_State()
{
	lastaction = Item;
	state = Prompt_S;
}

//calculate energy, check if action is possible. if not, go back to choose action.
void Battle::checkEnergy_State(int &energychange, Character *player)
{
	//get energy change
	energychange += player->get_EnergyDifference(lastaction);
	//check if action is possible with current energy
	if (player->stats.get_CurrEnergy() + energychange < 0)
	{
		//reset to default
		energychange = 0;
		cout << "You do not have enough energy to complete this action!" << endl;
		state = ChooseAction_S;
	}
	else if (figmentlist.size() > 1 && (lastaction == Swing || abilityChooseTarget)) //check if target needs to be specified when swinging or using ability that is multitarget
	{
		state = ChooseTarget_S;
	}
	else state = Prompt_S; //only one target
}

//outcome menu
void Battle::prompt_State(const int target, const int energychange, Character* player)
{
	//holds target information
	vector<Character*> allTargets;
	allTargets.push_back(&figmentlist[target]);

	//keep charging attack if necessary
	unsigned int chargeid = player->abilities.get_CurrentChargeId();
	if (chargeid != -1)
	{	
		//since we are already charging, allTargets is not important
		if (player == p1) loadInfo.p1AbilityTree.list[chargeid].ability->use_Ability(player, allTargets);
		else if (player == p2) loadInfo.p2AbilityTree.list[chargeid].ability->use_Ability(player, allTargets);
	}
	
	//based on last prompt, calculate action and display prompts
	switch (lastaction)
	{
		case Swing:
			for (unsigned int i = 0; i < allTargets.size(); ++i)
			{
				//PROMPT
				cout << player->get_Name() << " uses " << abs(player->stats.get_SwingEnergy()) << " energy and swings at " << allTargets[i]->get_Name() << "!" << endl;
				allTargets[i]->take_SwingDamage(player, 1.0);
			}
			check_Enemy(allTargets);
			break;
		case Ability:
			if (player == p1) loadInfo.p1AbilityTree.list[abilityId].ability->use_Ability(player, allTargets);
			else if (player == p2) loadInfo.p2AbilityTree.list[abilityId].ability->use_Ability(player, allTargets);
			check_Enemy(allTargets);
			break;
		case Defend:
			player->defend();
			break;
		case Item:
			break;
		case Wait:
			player->wait();
			break;
		case Run:
			runsuccessful = player->run();
			break;
	}
}

//check if any targeted enemies are defeated
void Battle::check_Enemy(vector<Character*> allTargets)
{
	//remove target from battlelog and figmentlist if figment is destroyed
	for(unsigned int i = 0; i < allTargets.size(); ++i)
	{ 
		if (!allTargets[i]->status.get_IsAlive())
		{
			//PROMPT
			cout << allTargets[i]->get_Name() << " is defeated!" << endl;
			
			//add appropriate experience, digits, and items
			add_Loot(allTargets[i]->level.get_Experience(), allTargets[i]->get_Digits());
			
			//erase figment
			figmentlist.erase(figmentlist.begin() + i);
		}
	}
}

//make decision in combat based on selected character's turn
void Battle::combatDecision(Character* c)
{	
	//reset initial state
	state = ChooseAction_S;
	
	//default target;
	int target = 0;
	//change in energy for an action
	int energychange = 0;
	//whether turn is over or not
	bool nextturn = false;
	
	if (c->status.get_IsPlayer()) //PLAYER TURN
	{
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
						chooseAbility_State(energychange, c);
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
		//enemy probability for certain actions
		float swingChance = 0.5;
		float abilityChance = 0.15;
		float defendChance = 0.15;
		float waitChance = 0.20;
		
		int enemyAction = Probability::multipleChanceToOccur(swingChance, abilityChance, defendChance, waitChance);
		//int enemyAction = Probability::multipleChanceToOccur(1, 0, 0, 0);
				
		//calculate energy and see if there is a better option.
		switch (enemyAction)
		{
			case Swing: //if not enough energy for swing, wait
				if (c->stats.get_SwingEnergy() > c->stats.get_CurrEnergy()) enemyAction = Wait;
				break;
			case Ability:
				break;
			case Wait: //if energy is full, choose either swing or ability
				if (c->stats.get_CurrEnergy() == c->stats.get_MaxEnergy())
				{
					if (Probability::chanceToOccur(0.5)) enemyAction = Swing;
					else enemyAction = Ability;
				}
			default:
				break;
		}
		
		//action
		switch (enemyAction)
		{
			case Swing:
			{
				Player *target;
				
				//choose which player to attack, first check if any players are wiped out
				if (!p1->status.get_IsAlive()) target = p2;
				else if (!p2->status.get_IsAlive()) target = p1;
				else if (Probability::chanceToOccur(0.5)) target = p1;
				else target = p2;
				
				//PROMPT
				cout << c->get_Name() << " uses " << abs(c->stats.get_SwingEnergy()) << " energy and swings at " << target->get_Name() << "!" << endl;
				target->take_SwingDamage(c, 1.0);
				break;
			}
			case Ability:
				//c->inflict_Ability();
				break;
			case Defend:
				c->defend();
				break;
			case Wait:
				c->wait();
				break;
			default:
				cerr << "Invalid enemy action. Exiting." << endl;
				exit(1);
		}
	}
	cout << endl;
	//figmentlist[target].showall_Stats();
}

//add loot to player: exp and money
void Battle::add_Loot(const unsigned int exp, const unsigned int digits)
{
	if (p1->status.get_IsAlive())
	{
		p1->level.change_Experience(exp);
		p1->change_Digits(digits);
		
		//get cumulative total for exp and digits
		p1ExpFinal += p1->level.get_Experience();
		p1DigitsFinal += p1->get_Digits();
	}
	if (p2->status.get_IsAlive())
	{
		p2->level.change_Experience(exp);
		p2->change_Digits(digits);		
		
		//get cumulative total for exp and digits
		p2ExpFinal += p2->level.get_Experience();
		p2DigitsFinal += p2->get_Digits();
	}
}

//level up player
void Battle::levelUp(Player* player)
{
	unsigned int levelsGained = 0;
	
	//level change checker
	while (player->level.checkLevelUp())
	{
		levelsGained++;
		player->level.change_Level(1);
	}
	
	//if any levels are gained, allow player to level up their stats and abilities
	if (levelsGained > 0)
	{
		cout << player->get_Name() << " gained " << levelsGained << " level(s)!" << endl;
		player->stats.levelUpStats(levelsGained);
		if (player == p1) 
		{
			player->abilities.set_AbilityList(loadInfo.p1AbilityTree.learn_Ability(levelsGained, player->abilities.get_AbilityList()));
		}
		else if (player == p2)
		{
			player->abilities.set_AbilityList(loadInfo.p2AbilityTree.learn_Ability(levelsGained, player->abilities.get_AbilityList()));
		}
		else
		{
			cout << "Invalid player while leveling up. Exiting." << endl;
			exit(1);
		}
		
	}
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
