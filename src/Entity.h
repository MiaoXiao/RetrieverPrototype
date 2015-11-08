#ifndef ENTITY_H
#define ENTITY_H

#include <string>

//handles all objects in game
class Entity
{
	public:
		//get name
		std::string get_Name() const;
		//set name
		void set_Name(const std::string v);
		
		//get description
		std::string get_Description() const;
		//set description
		void set_Description(const std::string v);
		
		//get id
		unsigned int get_Id() const;
		//set id
		void set_Id(unsigned int v);
		
	protected:
		//name of entity
		std::string name;
		
		//description of entity
		std::string description;
		
		//id of entity
		unsigned int id;
};

#endif
