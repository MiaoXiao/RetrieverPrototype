#ifndef HEALTHPERCENTAGE_H
#define HEALTHPERCENTAGE_H

#include "Food.h"
#include "Character.h"

#include <iostream>
#include <string>
#include <vector>

class HealthPercentage: public Food
{
	public:
		//CONSTRUCTOR: food
		HealthPercentage(std::string name, std::string description, const unsigned int size, const unsigned int value, const unsigned int type, const unsigned int id)
		{
			init_ItemInfo(name, description, size, value, type, id);
		}
		//CONSTRUCTOR: illuminite
		HealthPercentage(std::string name, std::string description, const unsigned int size, const unsigned int value, const unsigned int type, const unsigned int id,
			const unsigned int maxcharges)
		{
			init_ItemInfo(name, description, size, value, type, id);
			set_MaxCharges(maxcharges);
			set_CurrentCharges(maxcharges);
		}
		
		void use_Item(Character* user, std::vector<Character*> targets);
		
	private:
};

#endif

