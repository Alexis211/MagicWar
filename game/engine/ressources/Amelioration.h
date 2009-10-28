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
 *  	Amelioration.h
 *  	Header file for amelioration class
 *  	*/
#ifndef DEF_MW_AMELIORATION
#define DEF_MW_AMELIORATION

#include <engine/Parser.h>
#include <engine/characteristics.h>
#include <string>
#include <vector>
#include <map>

class UnitType;

struct Amelioration {
	std::string m_name;
	std::string m_description;
	std::vector<UnitType*> m_canBuild;
	std::vector<UnitType*> m_canProduce;
	std::vector<Amelioration*> m_requires;
	unit_c m_characteristics;

	void load(Parser& parser, std::map<std::string, Amelioration> other_ameliorations);
};

#endif
