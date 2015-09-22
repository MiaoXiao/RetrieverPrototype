#include "HealthPercentage.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
void HealthPercentage::use_Item(Character* user, std::vector<Character*> targets)
{
	cout << user->get_Name() << " uses " << get_Name() << "!" << endl;
	for (unsigned int i = 0; i < targets.size(); ++i)
	{
		 cout << targets[i]->get_Name() << " is healed for " << get_HealthGained() * targets[i]->stats.get_MaxHealth() << endl;
	}
	
	if (get_CurrentCharges() != 0)
	{
		change_CurrentCharges(-1);
		cout << user->get_Name() << " has " << get_CurrentCharges() << " left." << endl;
	}
}
//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
