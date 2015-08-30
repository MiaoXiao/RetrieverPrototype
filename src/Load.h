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

//max number of ability categories
#define CATEGORYCAP 3
//max number of ability types per category
#define TYPECAP 5

class Load
{
	public:
		//CONSTRUCTOR: //set capacity of ability pool vectors
		Load() 
		{
			p1AbilityPool.reserve(CATEGORYCAP);
			p2AbilityPool.reserve(CATEGORYCAP);
			
			for (unsigned int i = 0; i < CATEGORYCAP; ++i)
			{
				p1AbilityPool[i].reserve(TYPECAP);
				p2AbilityPool[i].reserve(TYPECAP);
			}
		}
		
		//loads all possible abilities
		void load_Abilities();
		
		//assign ability to correct character pool
		void assign_ToAbilityPool(Ability a, std::vector<std::string> usage, unsigned int category, unsigned int type);
		
		//get all abilities for p1
		std::vector< std::vector< std::vector<Ability> > > get_P1AbilityPool() const;
		//get all abilities for p2
		std::vector< std::vector< std::vector<Ability> > > get_P2AbilityPool() const;
		//get all abilities for e0
		std::vector< std::vector< std::vector<Ability> > > get_E0AbilityPool() const;
		//get all abilities for e1
		std::vector< std::vector< std::vector<Ability> > > get_E1AbilityPool() const;
		//get all abilities for e2
		std::vector< std::vector< std::vector<Ability> > > get_E2AbilityPool() const;
		//get all abilities for e3
		std::vector< std::vector< std::vector<Ability> > > get_E3AbilityPool() const;
		
	private:
		//manages ability category
		enum AbilityCategory {Attack_C, Support_C, Debuff_C};
		//manage ability types of all ability categories
		enum AttackAbilityType {Charged_T, Pierce_T, Area_T, Rapid_T};
		enum SupportAbilityType {StatBuff_T};
		enum DebuffAbilityType {StatDebuff_T};
		
		//player pools
		std::vector< std::vector< std::vector<Ability> > > p1AbilityPool;
		std::vector< std::vector< std::vector<Ability> > > p2AbilityPool;
		//enemy pools
		std::vector< std::vector< std::vector<Ability> > > e0AbilityPool;
		std::vector< std::vector< std::vector<Ability> > > e1AbilityPool;
		std::vector< std::vector< std::vector<Ability> > > e2AbilityPool;
		std::vector< std::vector< std::vector<Ability> > > e3AbilityPool;

};
#endif
