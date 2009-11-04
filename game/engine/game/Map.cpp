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
 *  	Map.cpp
 *  	Source code file for the map handling class
 *  	*/

#include "Map.h"
#include "Game.h"

#include <fstream>
#include <iostream>

using namespace std;

vector<string> Map::mapList;

Map::Map() {
	m_map = 0;
	m_width = 0;
	m_height = 0;
}

bool Map::load(string mapname, Game& g) {
	if (m_map != 0) return false;
	string filename = DATAPATH;
	filename += "/maps/" + mapname + ".map";
	ifstream map(filename.c_str(), ios::in);
	if (map) {
		map >> m_width >> m_height;
		m_map = new MapSquare[(m_width + 1) * (m_height + 1)];
		for (uint x = 0; x <= m_width; x++) {
			for (uint y = 0; y <= m_width; y++) {
				map >> at(x, y).height >> at(x, y).waterHeight >>
				   	at(x, y).texture >> at(x, y).textureVariant >> at(x, y).walkable;
			}
		}
		uint n; map >> n;
		for (uint i = 0; i < n; i++) {
			string t;
			float x, y;
			map >> t >> x >> y;
			if (UnitType::unitTypes.find(t) != UnitType::unitTypes.end()) {
				g.addUnit(&UnitType::unitTypes[t], &g.players()[0], Position(x, y, 0), true);
			}
		}
		for (uint i = 0; i < 8; i++) {
			map >> m_basesPositions[i].x >> m_basesPositions[i].y;
		}
		map.close();
	} else {
		throw Exception(string(_("Cannot load map file : ")) + filename, ERROR);
	}
	return true;
}

Point2D Map::basePos(int id) {
	if (id >= 0 and id < 0) return m_basesPositions[id];
	return Point2D(m_width / 2, m_height / 2);
}

MapSquare &Map::at(uint x, uint y) {
	if (x <= m_width and y <= m_height) return m_map[(x * (m_width + 1)) + y];
	return *((MapSquare*)0);
}
 void Map::loadList() {
	string filename = DATAPATH;
	filename += "/maps/maps.list";
	ifstream f(filename.c_str(), ios::in);
	if (f) {
		string l;
		while (!f.eof()) {
			getline(f, l);
			mapList.push_back(l);
		}
	} else {
		throw Exception(_("Cannot read map list"), ERROR);
	}
 }
