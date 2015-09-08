#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Globals.h"

#include <iostream>
#include <string>

struct Illuminite
{
	unsigned int charges = 0;
};

//handles all objects in game
class Item: public Entity
{
	public:
		//CONSTRUCTOR
		Item(const std::string name, const std::string description, const unsigned int size, const unsigned int value, const unsigned int type):
		size(size),
		value(value),
		type(type)
		{
			set_Name(name);
			set_Description(description);
		}
		
		//get size
		int get_Size() const;
		//get value
		int get_Value() const;
		
	private:
		//how much space this item takes up
		unsigned int size;
		//selling cost of item
		unsigned int value;
		//type of item
		unsigned int type;
		


};

#endif
