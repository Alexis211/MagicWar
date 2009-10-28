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
 *  	UnitType.h
 *  	Header file for unit type class
 *  	*/
#ifndef DEF_MW_UNITTYPE
#define DEF_MW_UNITTYPE

#include <map>
#include <string>
#include "Amelioration.h"

struct UnitType {
	std::string m_name;
	std::string m_description;
	std::vector<UnitType*> m_canBuild;
	std::vector<UnitType*> m_canProduce;
	unit_c m_characteristics;
	std::map<std::string, Amelioration> m_ameliorations;

	void load(std::string identifier);
	
	static std::map<std::string, UnitType> unitTypes;
	static void loadUnitTypes();
};

#endif
