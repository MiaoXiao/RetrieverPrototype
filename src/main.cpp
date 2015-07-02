#include <iostream>

#include "Player.h"
#include "Figment.h"

using namespace std;

int main() 
{
	Player p1("Tylor");
	Player p2("Liza");
	Figment f1(0, 1, 0, 0);
	f1.showall_Stats();
}
