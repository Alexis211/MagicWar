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

map<string, string> UnitType::defaultFormulas;
map<string, UnitType> UnitType::unitTypes;

void UnitType::loadUnitTypes() {
	string filename = DATAPATH;
	cout << _("Reading default formulas for units...") << endl;
	{
		ifstream file((filename + "/units/default.formulas").c_str(), ios::in); 
		if (file) {
			string s;
			while (getline(file, s)) {
				if (s == "" or s[0] == '#') continue;
				vector<string> t = SplitStr(s, '=');
				defaultFormulas.insert(make_pair(t[0], (t.size() > 1 ? t[1] : "0")));
			}
			file.close();
		} else {
			throw Exception(_("Cannot read default formulas file"), ERROR);
		}
	}
	cout << _("Loading unit types...") << endl;
	{
		ifstream file((filename + "/units/list").c_str(), ios::in);
		if (file) {
			string s;
			while (getline(file, s)) {
				if (s == "" or s[0] == '#') continue;
				unitTypes.insert(make_pair(s, UnitType()));
			}
			file.close();
		} else {
			throw Exception(_("Cannot read unit list"), ERROR);
		}
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
	try {
		p.loadFromFile(datafile);
	} catch (const Exception& e) {
		throw Exception(string(_("Cannot load data for unit ")) + idfier);
	}

	//Load global stuff
	p.setSection("global");
	m_name = p.getValueString("name", "NONAMED UNIT");
	m_description = p.getValueString("description", "NODESCRIPTED UNIT");
	m_productionSpeed = p.getValueInt("productionspeed", 0);
	m_cost.load(p, "cost");

	{	//Load build possibilities
		vector<string> cb = SplitStr(p.getValueString("canbuild", ""));
		for (unsigned int i = 0; i < cb.size(); i++) m_canBuild.push_back(&unitTypes[cb[i]]);
	}

	{	//Load production possibilities
		vector<string> cp = SplitStr(p.getValueString("canproduce", ""));
		for (unsigned int i = 0; i < cp.size(); i++) m_canProduce.push_back(&unitTypes[cp[i]]);
	}

	{	//Fetch amelioration list
		vector<string> aa = SplitStr(p.getValueString("activeameliorations", ""));
		for (unsigned int i = 0; i < aa.size(); i++) m_ameliorations.insert(make_pair(aa[i], Amelioration()));
	}
	
	p.setSection("formulas");
	{	//Load formulas
		map<string, string>::iterator it = defaultFormulas.begin();
		while (it != defaultFormulas.end()) {
			string f = p.getValueString(it->first, "");
			if (f == "") {
				m_info.set(it->first, it->second);
			} else {
				m_info.set(it->first, f);
			}
			it++;
		}
	}

	{	//Load ameliorations
		map<string, Amelioration>::iterator it = m_ameliorations.begin();
		while (it != m_ameliorations.end()) {
			it->second.load(p, it->first, m_ameliorations);
			it++;
		}
	}
}
