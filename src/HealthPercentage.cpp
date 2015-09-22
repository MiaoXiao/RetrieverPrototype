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
	
	//check if illuminite
	if (get_MaxCharges() != 0)
	{
		change_CurrentCharges(-1);
		cout << user->get_Name() << " has " << get_CurrentCharges() << " left." << endl;
	}
}

void HealthPercentage::get_ItemDescription()
{
	cout << get_Name() << endl;
	cout << "Weight: " << get_Size() << endl;
	cout << "Value: " << get_Value() << endl;
	if (get_MaxCharges() != 0)
	{
		cout << "Max Charges: " << get_MaxCharges() << endl;
		cout << "Charges Left: " << get_CurrentCharges() << endl;
	}
	cout << get_Description() << endl;
	cout << "User gains " << get_HealthGained() << "% of their maximum health back upon use." << endl;
	
}
//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
