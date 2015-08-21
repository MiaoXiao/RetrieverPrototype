#include "Globals.h"

using namespace std;

//returns random number between 0 and 1
float givePercentage() { return (double) rand() / (RAND_MAX); }

//will return true given probability, given number between 0 - 1
bool Probability::chanceToOccur(const float p)
{
	if (p < 0 || p > 1) 
	{
		cerr << "Probability not between 0 and 1. Exiting." << endl;
		exit(1);
	}
	
	return p >= givePercentage();
}

//based on multiple probabilities, returns 0, 1, 2, or 4 based on those probabilities
//neturn values return to CharacterChoice enum
int Probability::multipleChanceToOccur(const float prob0, const float prob1, const float prob2, const float prob3)
{
	float randnum = givePercentage();
	
	if (randnum <= prob0) return 0;
    randnum -= prob0;
    if (randnum <=prob1) return 1;
    randnum -= prob1;
    if (randnum <=prob2) return 2;
    randnum -= prob2;
    if (randnum <=prob3) return 4;
    
    cerr << "Could not finalize multipleChanceToOccur. Exiting." << endl;
    exit(1);
}

//return random number between lower bound and higher bound exclusive
int Probability::generateRandomNumber(const int lb, const int hb) { return rand() % hb + lb; }
