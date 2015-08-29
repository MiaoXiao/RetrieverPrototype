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
		
		//level range - up tp lv 9
		const int LEVELRANGE[50] = 
		{0, 50, 100, 200, 400, 800, 1600, 2400, 4800};
}

namespace Enemy
{
	//base values for level 1 figments
	const int STARTMH = 25;
	const int STARTME = 10;
	const int STARTREAC = 60;
	const int STARTS = 7;
	const int STARTR = 1;
	const int STARTE = 5;
	
	//path to find enemy stats
	const std::string PATH = "src/stats/";
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
