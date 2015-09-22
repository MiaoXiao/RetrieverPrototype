#ifndef HEALTHPERCENTAGE_H
#define HEALTHPERCENTAGE_H

#include "Food.h"
#include "Character.h"

#include <iostream>
#include <string>
#include <vector>

//heals user a percentage of their max health
class HealthPercentage: public Food
{
	public:
		//CONSTRUCTOR: food
		HealthPercentage(std::string name, std::string description, const unsigned int size, const unsigned int value, const unsigned int type, const unsigned int id,
			const float percentagehealed)
		{
			init_ItemInfo(name, description, size, value, type, id);
			set_HealthGained(percentagehealed);
		}
		//CONSTRUCTOR: illuminite
		HealthPercentage(std::string name, std::string description, const unsigned int size, const unsigned int value, const unsigned int type, const unsigned int id,
			const float percentagehealed,
			const unsigned int maxcharges)
		{
			init_ItemInfo(name, description, size, value, type, id);
			set_HealthGained(percentagehealed);
			set_MaxCharges(maxcharges);
			set_CurrentCharges(maxcharges);
		}
		
		void use_Item(Character* user, std::vector<Character*> targets);
		
		void get_ItemDescription();
	private:
};

#endif

