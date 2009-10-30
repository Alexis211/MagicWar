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
#include <iostream>
#include <engine/functions.h>

using namespace std;

map<string, UnitType> UnitType::unitTypes;

void UnitType::loadUnitTypes() {
	cout << _("Loading unit types...") << endl;
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
	cout << idfier << endl;
	string datafile = DATAPATH;
	datafile += "/units/" + idfier;
	Parser p;
	try {
		p.loadFromFile(datafile);
	} catch (const Exception& e) {
		throw Exception(string(_("Cannot load data for unit ")) + idfier);
	}

	m_name = p.getValueString("name", "NONAMED UNIT");
	m_description = p.getValueString("description", "NODESCRIPTED UNIT");
	m_productionSpeed = p.getValueInt("productionspeed", 0);
	m_characteristics.load(p);

	{
		vector<string> cb = SplitStr(p.getValueString("canbuild", ""));
		for (int i = 0; i < cb.size(); i++) m_canBuild.push_back(&unitTypes[cb[i]]);
	}

	{
		vector<string> cp = SplitStr(p.getValueString("canproduce", ""));
		for (int i = 0; i < cp.size(); i++) m_canProduce.push_back(&unitTypes[cp[i]]);
	}

	{
		vector<string> aa = SplitStr(p.getValueString("activeameliorations", ""));
		for (int i = 0; i < aa.size(); i++) m_ameliorations.insert(make_pair(aa[i], Amelioration()));
	}

	map<string, Amelioration>::iterator it = m_ameliorations.begin();
	while (it != m_ameliorations.end()) {
		cout << idfier << "." << it->first << endl;
		p.setSection(it->first);
		it->second.load(p, m_ameliorations);
		it++;
	}
}
