#include "Item.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//get size
int Item::get_Size() const {return size;}
//get value
int Item::get_Value() const {return value;}
//get value
int Item::get_Type() const {return type;}
//get value
int Item::get_MaxCharges() {return maxcharges;}
//get type
int Item::get_CurrentCharges() {return currentcharges;}

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

void Item::set_MaxCharges(const unsigned int v)
{
	maxcharges = v;
}

void Item::set_CurrentCharges(const unsigned int v)
{
	if (v >= currentcharges) currentcharges = maxcharges;
	else currentcharges = v;
}

void Item::change_CurrentCharges(const int v)
{
	if (v + currentcharges < 0) currentcharges = 0;
	else set_CurrentCharges(v + currentcharges);
}

//set all approrpriate information for each item
void Item::init_ItemInfo(string n, string d, const unsigned int s, const unsigned int v, const unsigned int t, const unsigned int i)
{
	set_Name(n);
	set_Description(d);
	set_Size(s);
	set_Value(v);
	set_Type(t);
	set_Id(i);
}
//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
