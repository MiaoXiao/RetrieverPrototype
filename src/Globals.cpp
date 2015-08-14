#include <iostream>

#include "Globals.h"

//will return true given probability, given number between 0 - 1
bool Probability::chanceToOccur(const float p)
{
	if (p < 0 || p > 1) 
	{
		std::cerr << "Probability not between 0 and 1. Exiting." << std::endl;
		exit(1);
	}
	
	return p >= (double) rand() / (RAND_MAX);
}

//return random number between lower bound and higher bound exclusive
int Probability::generateRandomNumber(const int lb, const int hb) { return rand() % hb + lb; }
