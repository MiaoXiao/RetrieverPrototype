#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <stdlib.h>

namespace Globals
{
		//no stat can go past this cap
		const int STAT_CAP = 100;
		//range of all swing attacks
		const int RANGE = 5;
		
		//level range - up tp lv 9
		const int LEVELRANGE[20] = 
		{0, 50, 100, 200, 400, 800, 1600, 2400, 4800};
}

namespace Probability
{
	//will return true given probability, given number between 0 - 1
	bool chanceToOccur(const float p);
	
	//return random number between lower bound and higher bound exclusive
	int generateRandomNumber(const int lb, const int hb);
}

#endif
