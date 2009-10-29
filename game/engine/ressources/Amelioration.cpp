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
 *  	Amelioration.cpp
 *  	Source code file for amelioration class
 *  	*/

#include "Amelioration.h"
#include "UnitType.h"

using namespace std;

void Amelioration::load(Parser& p, map<string, Amelioration> other_ameliorations) {
	m_name = p.getValueString("name", "NONAMED UNIT");
	m_description = p.getValueString("description", "NODESCRIPTED UNIT");
	m_characteristics.load(p);

	{
		string temp = p.getValueString("canbuild", ""), wat = "";
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == ' ') { 
				if (wat != "") m_canBuild.push_back(&UnitType::unitTypes[wat]);
				wat = "";
			} else {
				wat += temp[i];
			}
		}
		if (wat != "") m_canBuild.push_back(&UnitType::unitTypes[wat]);
	}

	{
		string temp = p.getValueString("canproduce", ""), wat = "";
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == ' ') { 
				if (wat != "") m_canProduce.push_back(&UnitType::unitTypes[wat]);
				wat = "";
			} else {
				wat += temp[i];
			}
		}
		if (wat != "") m_canProduce.push_back(&UnitType::unitTypes[wat]);
	}

	{
		string temp = p.getValueString("requires", ""), wat = "";
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == ' ') {
				if (wat != "") m_requires.push_back(&other_ameliorations[wat]);
				wat = "";
			} else {
				wat += temp[i];
			}
		}
		if (wat != "") m_requires.push_back(&other_ameliorations[wat]);
	}
}
