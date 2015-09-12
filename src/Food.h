#ifndef FOOD_H
#define FOOD_H

#include "Character.h"
#include "Item.h"

#include <iostream>

//handles all objects in game
class Food: public Item
{
	public:
		float get_HealthGained();
		
	protected:
		void set_HealthGained(const float v);
		
	private:
		//a percentage or flat value
		float healthgained;
};

#endif
