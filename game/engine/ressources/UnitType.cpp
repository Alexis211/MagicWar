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
 *  	UnitType.cpp
 *  	Source code file for unit type class
 *  	*/

#include <../config.h>
#include <engine/Exception.h>
#include <fstream>
#include "UnitType.h"

using namespace std;

map<string, UnitType> UnitType::unitTypes;

void UnitType::loadUnitTypes() {
	string unitlist = DATAPATH;
	unitlist += "/units/list";
	ifstream file(unitlist.c_str(), ios::in);
	if (file) {
		string s;
		while (getline(file, s)) {
			unitTypes.insert(make_pair(s, UnitType()));
		}
		file.close();
	} else {
		throw Exception(_("Cannot read unit list"), ERROR);
	}
	map<string, UnitType>::iterator it = unitTypes.begin();
	while (it != unitTypes.end()) {
		it->second.load(it->first);
		it++;
	}
}

void UnitType::load(string idfier) {
	string datafile = DATAPATH;
	datafile += "/units/" + idfier;
	Parser p;
	p.loadFromFile(datafile);

	m_name = p.getValueString("name", "NONAMED UNIT");
	m_description = p.getValueString("description", "NODESCRIPTED UNIT");
	m_characteristics.load(p);

	{
		string temp = p.getValueString("canbuild", ""), wat = "";
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == ' ') { 
				if (wat != "") m_canBuild.push_back(&unitTypes[wat]);
				wat = "";
			} else {
				wat += temp[i];
			}
		}
		if (wat != "") m_canBuild.push_back(&unitTypes[wat]);
	}

	{
		string temp = p.getValueString("canproduce", ""), wat = "";
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == ' ') { 
				if (wat != "") m_canProduce.push_back(&unitTypes[wat]);
				wat = "";
			} else {
				wat += temp[i];
			}
		}
		if (wat != "") m_canProduce.push_back(&unitTypes[wat]);
	}

	{
		string temp = p.getValueString("activeameliorations", ""), wat = "";
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == ' ') {
				if (wat != "") m_ameliorations.insert(make_pair(wat, Amelioration()));
				wat = "";
			} else {
				wat += temp[i];
			}
		}
		if (wat != "") m_ameliorations.insert(make_pair(wat, Amelioration()));
	}

	map<string, Amelioration>::iterator it = m_ameliorations.begin();
	while (it != m_ameliorations.end()) {
		p.setSection(it->first);
		it->second.load(p, m_ameliorations);
	}
}