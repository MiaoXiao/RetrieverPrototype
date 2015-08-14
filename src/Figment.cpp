#include "Figment.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
//assign starting stats based on parameters
void Figment::assign_Stats()
{
	//base values for level 1 figments
	int startMh = 25;
	int startMe = 10;
	int startReac = 60;
	int startS = 7;
	int startR = 1;
	int startE = 10;

	//FIX ME: levels currently have no effect
	stats.maxhealth = startMh + (startMh * healthX);
	stats.currhealth = stats.maxhealth;
	stats.maxenergy = startMe + (startMe * energyX);
	stats.currenergy = stats.maxenergy;
	stats.reaction = startReac + (startReac * reactionX);
	stats.swing = startS + (startS * swingX);
	stats.resistance = startR + (startR * resistanceX);
	
	if (name == "Tank") stats.evasiveness = 0;
	else stats.evasiveness = startE + (startE * evasivenessX);
}

//HELPER FUNCTION: changes attribute multipliers of figment based on type. return figment type
string Figment::chooseType(int t)
{
	switch (t)
	{
		//hatchlings
		case 0:
			healthX = -0.25;
			energyX = 1.0;
			swingX = -0.25;
			reactionX = 1.0;
			resistanceX = 1.0;
			evasivenessX = 1.0;
			return "Hatchling";
			break;
		//normals
		case 1:
			healthX = 1.0;
			energyX = 1.0;
			swingX = 1.0;
			reactionX = 1.0;
			resistanceX = 1.0;
			evasivenessX = 1.0;
			return "Normal";
			break;
		//tanks
		case 2:
			healthX = 10.0;
			energyX = 1.0;
			swingX = 1.0;
			reactionX = 0.5;
			resistanceX = 1.5;
			evasivenessX = 1.0;
			return "Tank";
			break;
		//swarms
		case 3:
			healthX = 1.0;
			energyX = 1.0;
			swingX = -0.25;
			reactionX = 2.0;
			resistanceX = 1.0;
			evasivenessX = 2.0;
			return "Swarm";
			break;
		//glassers
		case 4:
			healthX = -0.5;
			energyX = 1.0;
			swingX = 1.5;
			reactionX = 1.0;
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
