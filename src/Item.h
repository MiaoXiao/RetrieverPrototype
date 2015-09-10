#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Globals.h"
#include "Character.h"

#include <iostream>
#include <string>

//handles all objects in game
class Item: public Entity
{
	public:		
		//get size
		int get_Size() const;
		//get value
		int get_Value() const;
		//get type
		int get_Type() const;
		
	protected:
		//use specific item
		virtual void use_Item(Character* user, std::vector<Character*> targets) = 0;
		
		void set_Size(const unsigned int v);
		void set_Value(const unsigned int v);
		void set_Type(const unsigned int v);
		
	private:
		//how much space this item takes up
		unsigned int size;
		//selling cost of item
		unsigned int value;
		//type of item
		unsigned int type;
		
};

#endif
