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

//--------------------------------------------------------------------PROTECTED--------------------------------------------------------------------//

//--------------------------------------------------------------------PRIVATE--------------------------------------------------------------------//
