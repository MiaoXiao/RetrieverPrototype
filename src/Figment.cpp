#include "Figment.h"

#include <stdlib.h>
#include <time.h> 

//CONSTRUCTOR: creates normal figment based on type, difficulty
Figment::Figment(int type, int difficulty)
{
	chooseType(type);
}
//CONSTRUCTOR: creates evolved figment based on type, difficulty
Figment::Figment(int type, int difficulty, int numbperks)
{
	chooseType(type);
}

//assign starting stats based on parameters
void Figment::assign_Stats()
{

}

//changes attribute multipliers of figment based on type. return figment type
std::string Figment::chooseType(int t)
{
	switch (t)
	{
		//hatchlings
		case 0:
			swingX = -0.25;
			healthX = -0.25;
			hasteX = 1.0;
			resistanceX = 1.0;
			evasivenessX = 1.0;
			return "Hatchling";
			break;
		//normals
		case 1:
			swingX = 1.0;
			healthX = 1.0;
			hasteX = 1.0;
			resistanceX = 1.0;
			evasivenessX = 1.0;
			return "Normal";
			break;
		//tanks
		case 2:
			swingX = 1.0;
			healthX = 2.0;
			hasteX = 0.5;
			resistanceX = 1.5;
			evasivenessX = 0.0;
			return "Tank";
			break;
		//swarms
		case 3:
			swingX = -0.25;
			healthX = 1.00;
			hasteX = 2.0;
			resistanceX = 1.0;
			evasivenessX = 2.0;
			return "Swarm";
			break;
		//glassers
		case 4:
			swingX = 1.5;
			healthX = -0.5;
			hasteX = 1.0;
			resistanceX = 1.0;
			evasivenessX = 1.0;
			return "Glasser";
			break;
		//buddies
		case 5:
			break;
		//relics
		case 6:
			break;
		//flamers
		case 7:
			break;
		//fingers
		case 8:
			break;
		//shifters
		case 9:
			break;
		default:
			break;
	}
}