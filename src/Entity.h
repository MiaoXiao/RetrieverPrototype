#ifndef ENTITY_H
#define ENTITY_H

#include <string>

//handles all objects in game
class Entity
{
	public:
		//change name
		std::string get_Name() const;
		//set name
		void set_Name(const std::string n);
	protected:
		//name of entity
		std::string name;
};

#endif
