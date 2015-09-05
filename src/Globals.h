#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <vector>
#include <stdlib.h>

namespace Globals
{
	//no stat can go past this cap
	const int STAT_CAP = 100;
	//range of all swing attacks
	const int RANGE = 5;
	//probability to run
	const float RUNPROBABILITY = 0.2;
		
	//manages ability category
	enum ABILITYCATEGORY {Attack_C, Support_C, Debuff_C};
	//manage ability types of all ability categories
	enum ABILITYTYPE {Charged_T, Pierce_T, Area_T, Rapid_T};
}
namespace Probability
{
	//will return true given probability, given number between 0 - 1
	bool chanceToOccur(const float p);
	
	//based on multiple probabilities, returns 0, 1, 2, or 4 based on those probabilities
	//neturn values return to CharacterChoice enum
	int multipleChanceToOccur(const float prob0, const float prob1, const float prob2, const float prob3);
	
	//return random number between lower bound and higher bound exclusive
	int generateRandomNumber(const int lb, const int hb);
}

#endif
