#ifndef LOAD_H
#define LOAD_H

#include "Ability.h"
#include "Charged.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

class Load
{
	public:
		//CONSTRUCTOR:
		Load() 
		{
			
		}
		
		//loads all possible abilities
		void load_Abilities();
		
		//get all abilities for p1
		std::vector< std::vector< std::vector<Ability*> > > get_P1Abilities() const;
		//get all abilities for p2
		std::vector< std::vector< std::vector<Ability*> > > get_P2Abilities() const;
		
	private:
		std::vector<Charged> chargedAbilities;
	
		std::vector< std::vector< std::vector<Ability*> > > p1Abilities;
		std::vector< std::vector< std::vector<Ability*> > > p2Abilities;

};
#endif
