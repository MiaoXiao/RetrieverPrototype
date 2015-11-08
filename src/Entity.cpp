#include "Entity.h"

using namespace std;

//--------------------------------------------------------------------PUBLIC--------------------------------------------------------------------//
//change name
string Entity::get_Name() const {return name;}

//set name
void Entity::set_Name(const std::string v) {name = v;}

//change description
std::string Entity::get_Description() const {return description;}

//set description
void Entity::set_Description(const std::string v) {description = v;}

//get id
unsigned int Entity::get_Id() const {return id;}

//set id
void Entity::set_Id(unsigned int v) {id = v;}
//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
