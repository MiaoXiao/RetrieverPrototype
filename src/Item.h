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
		//get value
		int get_MaxCharges();
		//get type
		int get_CurrentCharges();
		
	protected:
		//use specific item
		virtual void use_Item(Character* user, std::vector<Character*> targets) = 0;
		
		void set_Size(const unsigned int v);
		void set_Value(const unsigned int v);
		void set_Type(const unsigned int v);
		
		void set_MaxCharges(const unsigned int v);
		void set_CurrentCharges(const unsigned int v);
		void change_CurrentCharges(const int v);
		
		//set all approrpriate information for each item
		void init_ItemInfo(std::string n, std::string d, const unsigned int s, const unsigned int v, const unsigned int t, const unsigned int i);
		
	private:
		//how much space this item takes up
		unsigned int size;
		//selling cost of item
		unsigned int value;
		//type of item
		unsigned int type;
		
		//maxcharges
		unsigned int maxcharges;
		//currentcharges
		unsigned int currentcharges;
		
};

#endif
