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
 *  	Faction.cpp
 *  	Source code file for faction class
 *  	*/

#include <../config.h>
#include <engine/Exception.h>
#include <fstream>
#include "Faction.h"
#include <iostream>
#include <engine/functions.h>

using namespace std;

vector<Faction> Faction::factions;

void Faction::loadFactions() {
	cout << _("Loading factions...") << endl;
	Faction temp = {_("Nature"), "", _("These units belong to the nature."), vector<UnitType*>()};
	factions.push_back(temp);

	Parser p;
	while (1) {
		try {
			p.loadFromFile(string(DATAPATH) + "/factions/" + Int2Str(factions.size()));
		} catch (const Exception& e) {
			break;
		}
		temp.m_name = p.getValueString("name", _("Faction with no name"));
		temp.m_singular = p.getValueString("singular", _("Unit with a faction with no name"));
		temp.m_description = p.getValueString("description", _("Faction that has no description"));
		temp.m_startsWith.clear();
		vector<string> units = SplitStr(p.getValueString("startswith", ""));
		for (int j = 0; j < units.size(); j++) temp.m_startsWith.push_back(&UnitType::unitTypes[units[j]]);
		factions.push_back(temp);
	}
}
