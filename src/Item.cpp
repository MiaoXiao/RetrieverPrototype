#include "Item.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//get size
int Item::get_Size() const {return size;}

//get value
int Item::get_Value() const {return value;}

//get value
int Item::get_Type() const {return type;}
	
//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//
void Item::set_Size(const unsigned int v)
{
	size = v;
}

void Item::set_Value(const unsigned int v)
{
	value = v;
}

void Item::set_Type(const unsigned int v)
{
	type = v;
}
		
//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
