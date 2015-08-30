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
		std::vector< std::vector< std::vector<Ability> > > get_P1Abilities() const;
		//get all abilities for p2
		std::vector< std::vector< std::vector<Ability> > > get_P2Abilities() const;
		
	private:
		//manage ability types of all ability categories
		enum AttackAbilityType {Charged_T, Pierce_T, Area_T, Rapid_T};
		enum SupportAbilityType {StatBuff_T};
		enum DebuffAbilityType {StatDebuff_T};

		enum AbilityCategory {Attack_C, Support_C, Debuff_C};
	
		//store charged attacks for all characters
		std::vector<Charged> chargedAbilities;
	
		std::vector< std::vector< std::vector<Ability> > > p1Abilities;
		std::vector< std::vector< std::vector<Ability> > > p2Abilities;

};
#endif
