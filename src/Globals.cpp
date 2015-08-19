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

//based on multiple probabilities, returns 0, 1, or 2 based on those probabilities
int Probability::multipleChanceToOccur(const float p0, const float p1, const float p2)
{
	float randnum = givePercentage();
	
	if (randnum <= p0) return 0;
    randnum -= p0;
    if (randnum <=p1) return 1;
    randnum -= p1;
    if (randnum <=p2) return 2;
    
    cerr << "Could not finalize multipleChanceToOccur. Exiting." << endl;
    exit(1);
}

//return random number between lower bound and higher bound exclusive
int Probability::generateRandomNumber(const int lb, const int hb) { return rand() % hb + lb; }
