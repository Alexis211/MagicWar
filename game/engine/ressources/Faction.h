/*
 * Copyright (C) 2009 AUVOLAT Alex
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*	MagicWar 0.1 alpha
 *	by Alexis211
 *  ----------------------------
 *  	Faction.h
 *  	Header file for faction class
 *  	*/
#ifndef DEF_MW_FACTION
#define DEF_MW_FACTION

#include "UnitType.h"
#include <vector>
#include <string>

struct Faction {
	std::string m_name;		//Group name, example :	administrators
	std::string m_singular;	//Unit name, example :	administrator
	std::string m_description;
	std::vector<UnitType*> m_startsWith;

	static std::vector<Faction> factions;
	static void loadFactions();
};

#endif
