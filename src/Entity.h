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
		void set_Name(const std::string v);
		
		//change description
		std::string get_Description() const;
		//set description
		void set_Description(const std::string v);
		
	protected:
		//name of entity
		std::string name;
		
		//description of entity
		std::string description;
};

#endif
